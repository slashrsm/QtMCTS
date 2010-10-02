/*
 * MCTSNode.cpp
 *
 *  Created on: 5.9.2009
 *      Author: slashrsm
 */

using namespace std;

#include "MCTSNode.h"
#include "MCTSPlayer.h"
#include "environment.h"
#include "GoToBorderGame.h"
#include "GoToCornerGame.h"
#include "GoToCornerDirectGame.h"
#include "Game.h"
#include "environment.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <list>
#include <fstream>

/*
 * Static members.
 */
int MCTSNode::SELECT_TRESSHOLD = 100;
float MCTSNode::UCT_C_CONSTANT = 0.7;
int MCTSNode::GO_TO_BORDER_MOVES_LIMIT = 100;
int MCTSNode::GO_TO_CORNER_MOVES_LIMIT = 100;
int MCTSNode::GO_TO_CHECKMATE_MOVES_LIMIT = 100;
int MCTSNode::TIMELIMIT = 10;					//timelimit for simulation - not used at all since simulations are VERY short
long MCTSNode::NODE_COUNT = 0;
int MCTSNode::MAX_DEPTH = 0;
long MCTSNode::SIMULATION_COUNT = 0;
long MCTSNode::CREATED_NODES = 0;
long MCTSNode::DELETED_NODES = 0;
long MCTSNode::ENTERED_EXPANSION = 0;
int MCTSNode::NODE_CREATION_FREQ = 0;
int MCTSNode::NODE_CREATION_COUNT = 0;
long MCTSNode::REACHED_CORNER_SIMS = 0;

/*
 * Constructors.
 */
MCTSNode::MCTSNode(QSharedPointer<Player> my, QSharedPointer<Player> his,
					bool my_turn=true, int depth_limit=100, MCTSNode* parent=NULL, char piece=-1, char move=-1, int depth=0, int type=Game::GO_TO_CHECKMATE) {
	this->parent = parent;
	this->my_player = my;
	this->his_player = his;
        this->my_player->set_oponent(this->his_player);
        this->his_player->set_oponent(this->my_player);
        this->my_player->register_to_pieces(this->my_player);
        this->his_player->register_to_pieces(this->his_player);


	this->depth = depth;
	this->depth_limit = depth_limit;
	this->visits = 0;
	this->wins = 0;
	this->my_turn = my_turn;
	this->piece_moved = piece;
	this->move = move;
	this->game_type = type;

	curr_player = my_turn ? this->my_player : this->his_player;
	curr_holder = my_turn ? this->his_player : this->my_player;

//	if (this->move != -1){
//		this->move_notation = this->curr_holder->situation->at(this->piece_moved)->position->get_notation();
//		this->piece_short_name = this->curr_holder->situation->at(this->piece_moved)->short_name();
//	}
//	else{
//		this->move_notation = NULL;
//	}

	MCTSNode::NODE_COUNT++;
	MCTSNode::CREATED_NODES++;
	if(this->depth > MCTSNode::MAX_DEPTH)
		MCTSNode::MAX_DEPTH = this->depth;
}

MCTSNode::~MCTSNode() {
	//delete children
//        for(int i=0; i<this->children.size(); i++){
//		delete this->children.at(i);
//	}

//	delete my_player;
//	delete his_player;

//	delete move_notation;

	MCTSNode::NODE_COUNT--;
	MCTSNode::DELETED_NODES++;
}

/*
 * Selecton phase.
 */
char MCTSNode::select(){
	if(MCTS_DEBUG) cout << "Entering SELECT phase at depth " << depth << endl;

	char result = 0;
	if(this->visits > SELECT_TRESSHOLD && this->children.size() > 0){

//		if (this->my_player != NULL){
//			delete this->my_player;
//			delete this->his_player;
//			this->my_player = NULL;
//			this->his_player = NULL;
//		}

                QSharedPointer<MCTSNode> best_child = this->children.at(0);
		float best_uct = best_child->UCT();
		float curr_uct = 0;
		int best_index = 0;
                for(int i=1; i<this->children.size(); i++){
			curr_uct = this->children.at(i)->UCT();
			if(curr_uct > best_uct){
				best_uct = curr_uct;
				best_index = i;
				best_child = this->children.at(i);
			}
		}

		//this->register_move(best_child->piece_moved, best_child->move);
		result = best_child->select();

	}
	else
		result = this->simulate();


	//WARNING: It seems like it was a really stupid bug here. Check if something doesen't works
	this->add_visit();
	this->wins += result;
	return result;
}

/*
 * Simulation phase.
 */
char MCTSNode::simulate(){
	if(MCTS_DEBUG) cout << "Entering SIMULATION phase at depth " << depth << endl;
	MCTSNode::SIMULATION_COUNT++;

	this->copy_situation();
	Game * sim = NULL;
	if(this->game_type == Game::GO_TO_BORDER)
                sim = new GoToBorderGame(my_player,his_player, MCTSNode::GO_TO_BORDER_MOVES_LIMIT-depth, MCTSNode::TIMELIMIT, "Simulation", "simulations.pgn", !my_turn, true);
	else if(this->game_type == Game::GO_TO_CORNER)
                sim = new GoToCornerGame(my_player,his_player, MCTSNode::GO_TO_CORNER_MOVES_LIMIT-depth, MCTSNode::TIMELIMIT, "Simulation", "simulations.pgn", !my_turn, true);
	else if(this->game_type == Game::GO_TO_CORNER_DIRECT)
                sim = new GoToCornerDirectGame(my_player,his_player, MCTSNode::GO_TO_CORNER_MOVES_LIMIT-depth, MCTSNode::TIMELIMIT, "Simulation", "simulations.pgn", !my_turn, true);
	else if(this->game_type == Game::GO_TO_CHECKMATE)
                sim = new Game(my_player,his_player, MCTSNode::GO_TO_CHECKMATE_MOVES_LIMIT-depth, MCTSNode::TIMELIMIT, "Simulation","simulations.pgn", !my_turn, true);

        QSharedPointer<Player> winner = sim->play();
	//sim.write_pgn();
//	char res = winner == my_player ? 1 : 0;  //temporary disabled because of next few lines
	char res = 0;
	if(winner == my_player)
		res = 1;
//	else if (winner == his_player)
//		res = 0;
	else
		res = 0;

	//store moves
        QList<char> moves;
        QList<int> pieces;
        QList<char> curr_moves = curr_player->move_history();
        QList<int> curr_pieces = curr_player->piece_history();
        QList<char> hold_moves = curr_holder->move_history();
        QList<int> hold_pieces = curr_holder->piece_history();
	int curr_size = curr_moves.size();
	int hold_size = hold_moves.size();
	int limit = max(curr_size, hold_size);
	for(int i=0; i<limit; i++){
		if(i < curr_size){
			moves.push_front(curr_moves.back());
			pieces.push_front(curr_pieces.back());
			curr_moves.pop_back();
			curr_pieces.pop_back();
		}

		if(i < hold_size){
			moves.push_front(hold_moves.back());
			pieces.push_front(hold_pieces.back());
			hold_moves.pop_back();
			hold_pieces.pop_back();
		}
	}

	//correct child subtree
	this->restore_situation();
	this->expanse(res, moves, pieces, depth);

	//register result and backpropagate
	delete sim;
	return res;
}

/*
 * Expansion phase.
 */
void MCTSNode::expanse(char res, QList<char> & moves, QList<int> & pieces, int sim_depth){
	if(MCTS_DEBUG) cout << "Entering EXPANSION phase at depth " << depth << endl;
        MCTSNode::ENTERED_EXPANSION++;

	this->add_visit();
	this->wins += res;

	if(this->visits != 1 && moves.size() > 0){
		int piece = pieces.back();
		char move = moves.back();

		pieces.pop_back();
		moves.pop_back();

		int next_index = this->get_move(piece, move);
		if(next_index == -1){
//			MCTSNode * new_node = new MCTSNode(my_player->duplicate(Player::APPROACH_KING_PLAYER),his_player->duplicate(Player::KBNK_LOOSER_PLAYER), !my_turn, depth_limit, this, piece, move, depth+1, this->game_type);
//			new_node->register_move(piece, move);
//			new_node->expanse(res, moves, pieces);
//			this->children.push_back(new_node);
//			if(MCTSNode::NODE_CREATION_COUNT == MCTSNode::NODE_CREATION_FREQ){
//				this->create_new_node(piece,move,res);
//				MCTSNode::NODE_CREATION_COUNT = 0;
//			}
//			else MCTSNode::NODE_CREATION_COUNT++;

			if(this->depth <= sim_depth+1)
				this->create_new_node(piece,move,res);
		}
		else{
                        QSharedPointer<MCTSNode> next_node = this->children.at(next_index);
			//this->register_move(next_node->piece_moved, next_node->move);
			next_node->expanse(res, moves, pieces,sim_depth);
		}
	}
}

/*
 * Returns best move on in current situation->
 */
QSharedPointer<MCTSNode> MCTSNode::best_move(){
	//get node with highest quality
	int best_index = 0;
        if (this->children.size() == 0)
            cout << "[MCTSNode::best_move()]Imamo problem" << endl;
//    int size = this->children.size();
	float best_quality = this->children.at(0)->quality();
	float curr_quality = 0;
        for(int i=0; i<this->children.size(); i++){
		curr_quality = this->children.at(i)->quality();
		if(curr_quality > best_quality){
			best_quality = curr_quality;
			best_index = i;
		}
	}
        QSharedPointer<MCTSNode> ret = this->children.at(best_index);
	ret->parent = NULL;

	//correct depths in tree
	ret->decrease_depth();

	//move in player
	//this->my_player->do_move(ret->move, ret->piece_moved);

	//return
	return ret;
}

/*
 * Returns quality of a given node.
 */
float MCTSNode::quality(){ return ((double) this->wins)/this->visits; }

/*
 * Decreases depth in tree.
 */
void MCTSNode::decrease_depth(){
        for(int i=0; i<this->children.size(); i++)
		this->children.at(i)->decrease_depth();

	this->depth--;
	this->depth_limit--;
}

/*
 * Oponent moved.
 */
QSharedPointer<MCTSNode> MCTSNode::oponent_moved(char piece, char move){
	int best_index = this->get_move(piece,move);

	//node was not found - have to create it
        QSharedPointer<MCTSNode> ret;
	if(best_index == -1){
		//cout << "[MCTSNode::opponent_moved()]On je fakin -1" << endl;
		best_index = this->create_new_node((int)piece,move,0);
	}

	ret = this->children.at(best_index);
	ret->parent = NULL;

	//correct depths in tree
	ret->decrease_depth();

	//move in player
	//this->his_player->do_move(move, piece);

	//return
	return ret;
}

/*
 * Returns UCT constant.
 */
float MCTSNode::UCT(){
	if(this->parent != NULL)
		return this->wins/((float)this->visits) + MCTSNode::UCT_C_CONSTANT * sqrt(log(this->parent->visits)/this->visits);
	else
		return 0;
//	return this->wins + MCTSNode::UCT_C_CONSTANT * sqrt(log(this->parent->visits)/this->visits);
}

/*
 * Returns index of searched move.
 */
int MCTSNode::get_move(char piece, char move){
        for(int i=0; i<this->children.size(); i++)
		if(this->children.at(i)->move == move && this->children.at(i)->piece_moved == piece)
			return i;

	return -1;
}

/*
 * Regiser move in players.
 */
void MCTSNode::register_move(char p, char m){
	this->curr_holder->do_move(m, p);
	this->curr_player->opponent_moved(m);
}

/*
 * Copies situation in players.
 */
void MCTSNode::copy_situation(){
	this->my_player->copy_situation();
	this->his_player->copy_situation();
}

/*
 * Restores situation in players.
 */
void MCTSNode::restore_situation(){
	this->his_player->restore_situation();
	this->my_player->restore_situation();
}

/*
 * Exports tree.
 */
void MCTSNode::export_graph(QTextStream & filename, int depth_limit){
        for(int i=0; i<this->children.size(); i++){
		filename << "\"";
		this->node_title(filename);
		filename << "\"";
		filename << " -> ";
		filename << "\"";
		this->children.at(i)->node_title(filename);
		filename << "\"" << endl;
	}

	filename << endl;

	if(this->depth < depth_limit){
                for(int i=0; i<this->children.size(); i++){
			this->children.at(i)->export_graph(filename, depth_limit);
		}
	}
}

/*
 * Prints node title.
 */
void MCTSNode::node_title(QTextStream & filename){
	if(this->move == -1)
		filename << "top\\n";
	else{
                QString notation = this->curr_holder->situation->at(this->piece_moved)->position->get_notation();
                filename << this->curr_holder->situation->at(this->piece_moved)->short_name();
                filename << notation;
                filename << "\\n";
	}
	filename << this->wins << "/" << this->visits << "\\n";
	filename << "Q: " <<  this->quality() << "\\n";
	filename << "UCT: " << this->UCT() << "\\n";
	if(this->parent != NULL)
		filename << "L&R: " << this->wins/((float)this->visits) << " - " << MCTSNode::UCT_C_CONSTANT * sqrt(log(this->parent->visits)/this->visits);

}

/*
 * Cretate new child node to current one and returns pointer to it.
 */
int MCTSNode::create_new_node(int piece, char move, char res){
        QSharedPointer<MCTSNode> new_node(new MCTSNode(my_player->duplicate(MCTSPlayer::MCTS_WHITE_SIM_TYPE),his_player->duplicate(MCTSPlayer::MCTS_BLACK_SIM_TYPE), !my_turn, depth_limit, this, piece, move, depth+1, this->game_type));
	new_node->register_move(piece, move);
	//new_node->expanse(res, moves, pieces);
	new_node->add_visit();
	new_node->wins += res;
	this->children.push_back(new_node);
	return this->children.size()-1;
}

/*
 * Adds visit.
 */
void MCTSNode::add_visit(){ this->visits += 1; }

