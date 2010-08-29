/*
 * Game.cpp
 *
 *  Created on: 1.8.2009
 *      Author: slashrsm
 */
using namespace std;

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

#include "environment.h"
#include "Player.h"
#include "Game.h"
#include "MCTSNode.h"


/*
 * Static members.
 */
int Game::GO_TO_BORDER = 0;
int Game::GO_TO_CORNER = 1;
int Game::GO_TO_CORNER_DIRECT = 3;
int Game::GO_TO_CHECKMATE = 4;

/*
 * Constructor.
 */
Game::Game(QSharedPointer<Player> w,QSharedPointer<Player> b, int maxmoves=100, int timelimit=10, QString event="", QString pgn="", bool black_on_turn=false, bool simulation=false) {
	this->white = w;
	this->black = b;

        w->register_to_pieces(w);
        b->register_to_pieces(b);
        w->set_oponent(b);
        b->set_oponent(w);

	this->timelimit = timelimit;
	this->maxmoves = maxmoves;
	this->black_on_turn = black_on_turn;
	this->simulation = simulation;
	this->event = event;
	this->pgn = pgn;

        if(this->event == "")
                this->event = "Unknown event";

        if(this->pgn == "")
                this->pgn = "game.pgn";

	//set player who starts to play
	this->on_move = this->black_on_turn ? this->black : this->white;
	this->on_hold = this->black_on_turn ? this->white : this->black;

	//prepare data for PGN write
        this->black_situation = "Black player";
        this->white_situation = "White player";
        this->result = "";

	this->generate_fen();
}

/*
 * Destructor.
 */
Game::~Game() {}

/*
 * Game play. It plays game in an infinite loop sice game is not ended.
 */
QSharedPointer<Player> Game::play(){
	//set moves count to 0
	this->moves = 0;

	//inic some local variables needed
	char move = -1;
        QSharedPointer<Player> tmp;

	//play game
	while(this->moves <= this->maxmoves && !this->game_ended()){
		//debug
//		if (this->simulation ) { //if (PRINT_EVERY_GAME_SITUATION) {
//			this->print_situation();
//		}

		//TODO delete!!!!
//		vector<char> black_sit = this->black->where_are_pieces();
//		int pos1 = this->black->situation->at(0)->position->get_positon();
//		int pos2 = this->white->situation->at(0)->position->get_positon();
//		char king = black_sit[pos1];

		move = this->on_move->move(this->timelimit);
		this->on_hold->opponent_moved(move);
		tmp = this->on_hold;
		this->on_hold = this->on_move;
		this->on_move = tmp;
		moves++;
	}

	return this->winner();
}

/*
 * Reports winner of a game. If game was drawn returns NULL.
 */
QSharedPointer<Player> Game::winner(){
        QSharedPointer<Player> winner;
	if(this->is_checkmate())
		winner = this->on_hold;
	else if (this->white_lost_piece() || this->is_stalemate())
		winner = this->black;
	else
                winner.clear();

	if(winner == NULL)
                this->result += "1/2-1/2";
	else if (winner == this->white)
                this->result += "1-0";
	else if (winner == this->black)
                this->result += "0-1";


        //check if simulation ended in corner
        if(this->simulation){
            if(this->is_in_corner())
                MCTSNode::REACHED_CORNER_SIMS++;
        }

	return winner;
}

/*
 * Checks if game has ended.
 */
bool Game::game_ended(){ return this->cannot_move() || this->white_lost_piece(); } //return this->is_checkmate() || this->is_stalemate(); }

/*
 * Checks if it is a checkmate situation->
 */
bool Game::is_checkmate(){ return this->is_check() && this->cannot_move(); }

/*
 * Checks if it is a stalmate situation->
 */
bool Game::is_stalemate(){ return !this->is_check() && this->cannot_move(); }

/*
 * Checks if it is a check situation->
 */
bool Game::is_check(){
        QVector<bool> hold_reach = this->on_hold->my_reach();
        return hold_reach[this->on_move->situation->at(0)->position->get_positon()];
}

/*
 * Checks if player on move cannot move a piece.
 */
bool Game::cannot_move(){
        QVector<bool> move_reach = this->on_move->my_moves();
	bool ret = false;
	for (int i = 0; i < BOARD_SIZE; ++i)
		ret |= move_reach[i];

	return !ret;
}


/*
 * Checks if white still has 3 pieces.
 */
bool Game::white_lost_piece(){ return this->white->situation->size() < 3; }

/*
 * Prints situation so std output.
 */
void Game::print_situation(){
        QVector<char> black_sit = this->black->where_are_pieces();
        QVector<char> white_sit = this->white->where_are_pieces();

	cout << "--- Situation: ---" << endl;
	cout << "  A B C D E F G H  " << endl;
	for (int i = 7; i >= 0; i--) {
		cout << i+1 << " ";
		for (int j = 0; j < 8; ++j) {
			if(white_sit[i*8+j] != '_')
				cout << white_sit[i*8+j] << ' ';
			else if (black_sit[i*8+j] != '_')
				cout << (char)(black_sit[i*8+j]+32) << ' ';
			else
				cout << '_' << ' ';
		}
		cout << i+1 << endl;
	}
	cout << "  A B C D E F G H  " << endl << endl;
}

/*
 * Writes game to pgn.
 */
void Game::write_pgn(){
    //inic loc vars: length of play, player with more moves
    int b_size = this->black->get_pgn_size(), w_size = this->white->get_pgn_size();
    int limit = max(w_size, b_size);

    //calculate date
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [15];

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    strftime (buffer,15,"%d. %b %Y",timeinfo);

    //open file
    QFile f(this->pgn);
    f.open(QIODevice::Append);
    QTextStream pgn_file(&f);

    //write header
    pgn_file << "[Event \"" << (this->event) << "\"]" << endl;
    pgn_file << "[Site \"MCTS KBNK simulation (by: JAnez Urevc, janez@janezek.org)\"]" << endl;
    pgn_file << "[Date \"" << buffer << "\"]" << endl;
    pgn_file << "[Round \"?\"]" << endl;
    pgn_file << "[White \"" << (this->white_situation) << "\"]" << endl;
    pgn_file << "[Black \"" << (this->black_situation) << "\"]" << endl;
    pgn_file << "[Result \"" << (this->result) << "\"]" << endl;
    pgn_file << "[SetUp \"1\"]" << endl;
    pgn_file << "[FEN \"" << (this->fen) << "\"]" << endl;
    pgn_file << "[PlyCount \"" << w_size + b_size << "\"]" << endl;

    //write moves
    for (int i = 0; i < limit; ++i) {
    	//add a newline every once and while
    	if(i % 5 == 0)
    		pgn_file << endl;

        pgn_file << i+1 << ". ";
        pgn_file << this->white->get_pgn(i) << ' ';
        if(i < b_size){
                pgn_file << this->black->get_pgn(i) << ' ';
    	}
    }

    pgn_file << endl << endl << endl;
    f.close();
}

/*
 * Generates FEN line for PGN file.
 */
void Game::generate_fen(){
	//inic FEN
        this->fen = "";

	//get situation of both players
        QVector<char> w_sit = this->white->where_are_pieces();
        QVector<char> b_sit = this->black->where_are_pieces();

	//calculate initial position set
	int free;
	char w_pos, b_pos;
	for (int i = 7; i >= 0; --i) {
		free = 0;
		for (int j = 0; j < 8; ++j) {
			w_pos = w_sit[8*i+j];
			b_pos = b_sit[8*i+j];

			if (w_pos == '_' && b_pos == '_')
				free++;
			else {
				if (free > 0)
                                        this->fen += (char)(free+48);

                                this->fen += (w_pos != '_') ? (char)(w_pos) : (char)(b_pos+32);
				free = 0;
			}
		}
		if (free > 0)
                        this->fen += free+48;
		if(i != 0)
                        this->fen += '/';
	}

	//choose starting player
        this->fen += " ";
        this->fen += this->black_on_turn ? 'b' : 'w';

        this->fen += " - - 0 1";
}

/*
 * Checks if black king is in right corner.
 */
bool Game::is_in_corner(){
    // Find his Bishop
    QSharedPointer<Piece> w_bishop;
    for (int i=0; i < this->white->situation->size(); i++)
        if (this->white->situation->at(i)->short_name() == 'B')
            w_bishop = this->white->situation->at(i);


    // Check Bishop color and corners
    if (w_bishop != NULL){
        char bishop_color = w_bishop->position->get_color();
        char king_pos = this->black->situation->at(0)->position->get_positon();

        return (bishop_color == 'W' && (king_pos == 7 || king_pos == 56)) || (bishop_color == 'B' && (king_pos == 0 || king_pos == 63));
    }

    return false;
}
