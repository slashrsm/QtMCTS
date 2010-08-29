/*
 * MCTSPlayer.cpp
 *
 *  Created on: 5.9.2009
 *      Author: slashrsm
 */

using namespace std;

#include "MCTSPlayer.h"
#include "MCTSNode.h"
#include "environment.h"
#include "Game.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

/*
 * Constructors.
 */
MCTSPlayer::MCTSPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > > sit) : Player(sit) {}

MCTSPlayer::~MCTSPlayer() {}

/*
 * Initialize tree.
 */
void MCTSPlayer::set_oponent(QSharedPointer<Player> op){
        this->opponent = op;

	//register him
        for(int i=0; i<situation->size(); i++)
                this->situation->at(i)->his_player = this->opponent;

	this->game_state = -1;
}

/*
 * Plays a move regarding a MCTS simulations played in a
 * time period given.
 */
char MCTSPlayer::move(int timelimit){
	MCTSNode::SIMULATION_COUNT = 0;
        QSharedPointer<MCTSNode> old_tree;
	int start_time = clock();
	int curr_time = clock();

	//set new state if needed
	this->check_simulation_game();

	//run simulations until have time
	while(((double)(curr_time - start_time))/CLOCKS_PER_SEC < timelimit){
//		this->tree->copy_situation();

		if(MCTS_DEBUG) cout << "Starting MCTS." << endl;
		this->tree->select();

//		this->tree->restore_situation();
		curr_time = clock();
	}

        //printout graph
        QString name = "tree-";
        name += QString::number(this->pgn_moves.size());
        name += "-0.dot";
	this->export_graph(name, 0);

        //printout graph
//        QString n_full_1 = "full-tree-"+(int)this->pgn_moves.size()+"-0.dot";
//	this->export_graph(n_full_1, 100);

	//get best move and set new root of tree
	old_tree = this->tree;
	this->tree = old_tree->best_move();

//	printout graph
        QString name1 = "tree-";
        name1 += QString::number(this->pgn_moves.size());
        name1 += "-1.dot";
        this->export_graph(name1, 0);

	//printout graph
//        QString n_full_2 = "full-tree-"+(int)this->pgn_moves.size()+"-1.dot";
//	this->export_graph(n_full_2, 100);


	if(MCTS_DEBUG) cout << "MCTS moved: " << (int)this->tree->piece_moved << ", " << (int)this->tree->move << endl;
	cout << "--==Statistics==--" << endl;
	cout << "\tMax tree depth: " << MCTSNode::MAX_DEPTH << endl;
	cout << "\tNode count: " << MCTSNode::NODE_COUNT << endl;
        cout << "\tSimulation count: " << MCTSNode::SIMULATION_COUNT << endl;
        cout << "\tEnds in corner: " << MCTSNode::REACHED_CORNER_SIMS << endl << endl;
        MCTSNode::MAX_DEPTH = 0;
        MCTSNode::REACHED_CORNER_SIMS = 0;


	return this->do_move(this->tree->move, this->tree->piece_moved);
}

/*
 * Checks if we loast a piece.
 */
void MCTSPlayer::opponent_moved(char his_move){
	//check if some piece was taken and remove it
        QSharedPointer<Piece> curr_piece;
	char curr_pos = -1;
        for (int i=0; i < this->situation->size(); ++i) {
                curr_piece = this->situation->at(i);
		curr_pos = curr_piece->position->get_positon();
		if (his_move == curr_pos){
                        this->situation->erase(this->situation->begin()+i);
			break;
		}
	}

        QSharedPointer<MCTSNode> old_tree = this->tree;
	this->tree = old_tree->oponent_moved(0,his_move);
}

/*
 * Exports tree.
 */
void MCTSPlayer::export_graph(QString filename, int depth_limit){
    //open file
    QFile f(filename);
    f.open(QIODevice::WriteOnly);
    QTextStream dot_file(&f);

    //write header
    dot_file << "digraph \"tree after " << this->pgn_moves.size() <<" moves\" {" << endl;
    dot_file << "\tnode [color=Black,fontcolor=Blue,font=Courier]" << endl;

    //write tree
    this->tree->export_graph(dot_file, depth_limit);

    //close file
    dot_file << "}" <<  endl << endl << endl;
    f.close();
}


/**
 * Check if we need to change game state.
 */
void MCTSPlayer::check_simulation_game(){
	int maxdepth = this->game_state == -1 ? 100 : 100-this->tree->depth;

	if(is_in_corner_area()){
		if(this->game_state != Game::GO_TO_CHECKMATE){
                        QSharedPointer<MCTSNode> n(new MCTSNode(this->duplicate(Player::KBNK_WINNER_PLAYER), opponent.toStrongRef()->duplicate(Player::RANDOM_PLAYER), true, maxdepth, NULL, -1, -1, 0, Game::GO_TO_CHECKMATE));
                        this->tree = n;
			this->game_state = Game::GO_TO_CHECKMATE;
			cout << "MCTSPlayer: changed to GO_TO_CHECKMATE mode." << endl;
		}
	}
//	else if(is_at_border()){
//		if(this->game_state != Game::GO_TO_CORNER){
//			this->tree = new MCTSNode(this->duplicate(Player::KBNK_WINNER_PLAYER), opponent->duplicate(Player::KBNK_LOOSER_PLAYER), true, 100, NULL, -1, -1, 0, Game::GO_TO_CORNER);
//			this->game_state = Game::GO_TO_CORNER;
//			cout << "MCTSPlayer: changed to GO_TO_CORNER mode." << endl;
//		}
//	}
	else {
		if(this->game_state != Game::GO_TO_CORNER_DIRECT){
                        QSharedPointer<MCTSNode> n(new MCTSNode(this->duplicate(Player::KBNK_WINNER_PLAYER), opponent.toStrongRef()->duplicate(Player::RANDOM_PLAYER), true, maxdepth, NULL, -1, -1, 0, Game::GO_TO_CORNER_DIRECT));
                        this->tree = n;
			this->game_state = Game::GO_TO_CORNER_DIRECT;
			cout << "MCTSPlayer: changed to GO_TO_CORNER_DIRECT mode." << endl;
		}
	}
//	else{
//		if(this->game_state != Game::GO_TO_BORDER){
//			this->tree = new MCTSNode(this->duplicate(Player::KBNK_WINNER_PLAYER), opponent->duplicate(Player::KBNK_LOOSER_PLAYER), true, 100, NULL, -1, -1, 0, Game::GO_TO_BORDER);
//			this->game_state = Game::GO_TO_BORDER;
//			cout << "MCTSPlayer: changed to GO_TO_BORDER mode." << endl;
//		}
//	}
//	if(this->game_state == -1){
//		this->tree = new MCTSNode(this->duplicate(Player::KBNK_WINNER_PLAYER), opponent->duplicate(Player::KBNK_LOOSER_PLAYER), true, 100, NULL, -1, -1, 0, Game::GO_TO_CHECKMATE);
//		this->game_state = Game::GO_TO_CHECKMATE;
//		cout << "MCTSPlayer: changed to GO_TO_CHECKMATE mode." << endl;
//	}
}

/**
 * Check if his king is in right corner.
 */
bool MCTSPlayer::is_in_corner(){
        char pos = this->opponent.toStrongRef()->situation->at(0)->position->get_positon();
	bool ret = pos == 0 || pos == 7 || pos == 56 || pos == 63;
	if(ret){
                QSharedPointer<Piece> p;
                for(int i=0; i<this->situation->size(); i++){
                        p = this->situation->at(i);
			if(p->short_name() == 'B')
				break;
		}

                QVector<char> bishop_coords = p->position->get_coords();
		if((bishop_coords[0] + bishop_coords[1]) % 2 == 0 && (pos == 56 || pos == 7))
			ret = false;
		else if((bishop_coords[0] + bishop_coords[1]) % 2 == 1 && (pos == 0 || pos == 63))
                        ret = false;
	}
	return ret;
}

/**
 * Check if king is in right corner + 1 positon around.
 */
bool MCTSPlayer::is_in_corner_area(){
        QSharedPointer<Piece> his_king = this->opponent.toStrongRef()->situation->at(0);
	bool ret = his_king->mdistance_to_pos(0) < 2 || his_king->mdistance_to_pos(7) < 2;
	ret |= his_king->mdistance_to_pos(56) < 2 || his_king->mdistance_to_pos(63) < 2;
	if(ret){
                QSharedPointer<Piece> p;
                for(int i=0; i<this->situation->size(); i++){
                        p = this->situation->at(i);
			if(p->short_name() == 'B')
				break;
		}

                QVector<char> bishop_coords = p->position->get_coords();
		if((bishop_coords[0] + bishop_coords[1]) % 2 == 0 && (his_king->mdistance_to_pos(56) < 2 || his_king->mdistance_to_pos(7) < 2))
			ret = false;
		else if((bishop_coords[0] + bishop_coords[1]) % 2 == 1 && (his_king->mdistance_to_pos(0) < 2 || his_king->mdistance_to_pos(63) < 2))
                        ret = false;
	}
	return ret;
}

/**
 * Check is his king is at the border.
 */
bool MCTSPlayer::is_at_border(){
        QVector<char> coords = this->opponent.toStrongRef()->situation->at(0)->position->get_coords();
        bool ret = coords[0] == 0 || coords[0] == 7 || coords[1] == 0 || coords[1] == 7;
	return ret;
}
