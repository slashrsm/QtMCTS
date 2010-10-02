/*
 * Knight.cpp
 *
 *  Created on: 8.8.2009
 *      Author: slashrsm
 */

using namespace std;

#include <iostream>

#include "environment.h"
#include "Knight.h"

/*
 * Constructors.
 */
Knight::Knight(QSharedPointer<Position> pos, bool white) : Piece(pos, white) {
	// TODO Auto-generated constructor stub

}

Knight::~Knight() {
}

/*
 * Calculates reach.
 */
QVector<bool> & Knight::reach(){
	if(this->saved_reach.empty()){
                this->saved_reach.fill(false,64);
		char index = (this->position)->get_positon();

		if(index >= 17) this->saved_reach[index-17]  =true;
		if(index >= 15) this->saved_reach[index-15]  =true;
		if(index >= 10) this->saved_reach[index-10]  =true;
		if(index >= 6) this->saved_reach[index-6]  =true;
		if(index <= BOARD_SIZE-7) this->saved_reach[index+6]  =true;
		if(index <= BOARD_SIZE-11) this->saved_reach[index+10]  =true;
		if(index <= BOARD_SIZE-16) this->saved_reach[index+15]  =true;
		if(index <= BOARD_SIZE-18) this->saved_reach[index+17]  =true;

		if(index % 8 < 2){
			if(index >= 10) this->saved_reach[index-10]  =false;
			this->saved_reach[index+6]  =false;
			if(index % 8 < 1){
				if(index >= 17) this->saved_reach[index-17]  =false;
				if(index <= BOARD_SIZE-16) this->saved_reach[index+15]  =false;
			}
		}
		else if (index % 8 > 5) {
			if(index >= 6) this->saved_reach[index-6]  =false;
			if(index <= BOARD_SIZE-11) this->saved_reach[index+10]  =false;
			if( index % 8 > 6){
				if(index >= 15) this->saved_reach[index-15]  =false;
				if(index <= BOARD_SIZE-18) this->saved_reach[index+17]  =false;
			}
		}

		if(index / 8 < 2){
			if(index >= 17) this->saved_reach[index-17]  =false;
			if(index >= 15) this->saved_reach[index-15]  =false;
			if(index / 8 < 1){
				if(index >= 10) this->saved_reach[index-10]  =false;
				if(index >= 6) this->saved_reach[index-6]  =false;
			}
		}
		else if (index / 8 > 5) {
			if(index <= BOARD_SIZE-16) this->saved_reach[index+15]  =false;
			if(index <= BOARD_SIZE-18) this->saved_reach[index+17]  =false;
			if (index / 8 > 6) {
				if(index <= BOARD_SIZE-7) this->saved_reach[index+6]  =false;
				if(index <= BOARD_SIZE-11) this->saved_reach[index+10]  =false;
			}
		}

		//debug output
		if(PRINT_REACH){
			cout << "Knight: " << endl;
			this->print_array(this->saved_reach);
		}

		return this->saved_reach;
	}
	else {
		return this->saved_reach;
	}
}

/*
 * Calculates moves.
 */
QVector<bool>& Knight::moves(){
	if(this->saved_moves.empty()){
                QVector<char> where = this->my_player.toStrongRef()->where_are_pieces();
                this->saved_moves.fill(false,64);
		char index = this->position->get_positon();
                char king = this->his_player.toStrongRef()->situation->at(0)->position->get_positon();

		//check not to move on my player
		if(index >= 17) this->saved_moves[index-17]  = where[index-17] == '_' ? true : false;
		if(index >= 15) this->saved_moves[index-15]  = where[index-15] == '_' ? true : false;
		if(index >= 10) this->saved_moves[index-10]  = where[index-10] == '_' ? true : false;
		if(index >= 6) this->saved_moves[index-6]  = where[index-6] == '_' ? true : false;
		if(index <= BOARD_SIZE-7) this->saved_moves[index+6]  = where[index+6] == '_' ? true : false;
		if(index <= BOARD_SIZE-11) this->saved_moves[index+10]  = where[index+10] == '_' ? true : false;
		if(index <= BOARD_SIZE-16) this->saved_moves[index+15]  = where[index+15] == '_' ? true : false;
		if(index <= BOARD_SIZE-18) this->saved_moves[index+17]  = where[index+17] == '_' ? true : false;

		if(index % 8 < 2){
			if(index >= 10) this->saved_moves[index-10]  =false;
			this->saved_moves[index+6]  =false;
			if(index % 8 < 1){
				if(index >= 17) this->saved_moves[index-17]  =false;
				if(index <= BOARD_SIZE-16) this->saved_moves[index+15]  =false;
			}
		}
		else if (index % 8 > 5) {
			if(index >= 6) this->saved_moves[index-6]  =false;
			if(index <= BOARD_SIZE-11) this->saved_moves[index+10]  =false;
			if( index % 8 > 6){
				if(index >= 15) this->saved_moves[index-15]  =false;
				if(index <= BOARD_SIZE-18) this->saved_moves[index+17]  =false;
			}
		}

		if(index / 8 < 2){
			if(index >= 17) this->saved_moves[index-17]  =false;
			if(index >= 15) this->saved_moves[index-15]  =false;
			if(index / 8 < 1){
				if(index >= 10) this->saved_moves[index-10]  =false;
				if(index >= 6) this->saved_moves[index-6]  =false;
			}
		}
		else if (index / 8 > 5) {
			if(index <= BOARD_SIZE-16) this->saved_moves[index+15]  =false;
			if(index <= BOARD_SIZE-18) this->saved_moves[index+17]  =false;
			if (index / 8 > 6) {
				if(index <= BOARD_SIZE-7) this->saved_moves[index+6]  =false;
				if(index <= BOARD_SIZE-11) this->saved_moves[index+10]  =false;
			}
		}

		//check not to eat his king
		this->saved_moves[king] = false;

		//debug output
		if(PRINT_MOVES)
			this->print_array(this->saved_moves);

		return this->saved_moves;
	}
	else {
		return this->saved_moves;
	}
}

/*
 * Returns short name of this piece.
 */
char Knight::short_name(){ return 'N'; }
