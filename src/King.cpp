/*
 * King.cpp
 *
 *  Created on: 1.8.2009
 *      Author: slashrsm
 */

using namespace std;

#include <cstring>
#include <iostream>

#include "environment.h"
#include "King.h"

King::King(QSharedPointer<Player> my, QSharedPointer<Player> his, QSharedPointer<Position> pos, bool white) : Piece(my, his, pos, white)  {}

King::~King(){}

/*
 * Calculates reach.
 */
QVector<bool> & King::reach(){
	if(this->saved_reach.empty()){
                this->saved_reach.fill(false,BOARD_SIZE);
		char index = (this->position)->get_positon();

		if(index >= 9) this->saved_reach[index-9]  =true;
		if(index >= 8) this->saved_reach[index-8]  =true;
		if(index >= 7) this->saved_reach[index-7]  =true;
		if(index >= 1) this->saved_reach[index-1]  =true;

		if(index <= BOARD_SIZE-2) this->saved_reach[index+1]  =true;
		if(index <= BOARD_SIZE-8) this->saved_reach[index+7]  =true;
		if(index <= BOARD_SIZE-9) this->saved_reach[index+8]  =true;
		if(index <= BOARD_SIZE-10) this->saved_reach[index+9]  =true;

		if(index % 8 == 0){
			if (index >= 9) this->saved_reach[index-9]  =false;
			if (index >= 1) this->saved_reach[index-1]  =false;
			if (index <= BOARD_SIZE - 8) this->saved_reach[index+7]  =false;
		}
		else if (index % 8 == 7) {
			if (index >= 7) this->saved_reach[index-7]  =false;
			if (index <= BOARD_SIZE - 2) this->saved_reach[index+1]  =false;
			if (index <= BOARD_SIZE - 10) this->saved_reach[index+9]  =false;
		}

		if( index/8 == 0 ){
			if (index >= 9) this->saved_reach[index-9]  =false;
			if (index >= 8) this->saved_reach[index-8]  =false;
			if (index >= 7) this->saved_reach[index-7]  =false;
		}
		else if (index/8 == 7) {
			if (index <= BOARD_SIZE - 8) this->saved_reach[index+7]  =false;
			if (index <= BOARD_SIZE - 9) this->saved_reach[index+8]  =false;
			if (index <= BOARD_SIZE - 10) this->saved_reach[index+9]  =false;
		}

		//debug output
		if(PRINT_REACH){
			cout << "King: " << endl;
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
QVector<bool>& King::moves(){
	if (this->saved_moves.empty()) {
                QVector<bool> reach = this->his_player.toStrongRef()->my_reach();
                QVector<char> where = this->my_player.toStrongRef()->where_are_pieces();
                this->saved_moves.fill(false,BOARD_SIZE);
		char index = this->position->get_positon();
                char king = this->his_player.toStrongRef()->situation->at(0)->position->get_positon();

		//check not to move on my player
		if(index >= 9) this->saved_moves[index-9]  = where[index-9] == '_' ? true : false;
		if(index >= 8) this->saved_moves[index-8]  = where[index-8] == '_' ? true : false;
		if(index >= 7) this->saved_moves[index-7]  = where[index-7] == '_' ? true : false;
		if(index >= 1) this->saved_moves[index-1]  = where[index-1] == '_' ? true : false;
		if(index <= BOARD_SIZE-2) this->saved_moves[index+1]  = where[index+1] == '_' ? true : false;
		if(index <= BOARD_SIZE-8) this->saved_moves[index+7]  = where[index+7] == '_' ? true : false;
		if(index <= BOARD_SIZE-9) this->saved_moves[index+8]  = where[index+8] == '_' ? true : false;
		if(index <= BOARD_SIZE-10) this->saved_moves[index+9]  = where[index+9] == '_' ? true : false;

		if(index % 8 == 0){
			if (index >= 9) this->saved_moves[index-9]  = false;
			if (index >= 1) this->saved_moves[index-1]  = false;
			if (index <= BOARD_SIZE-8) this->saved_moves[index+7]  = false;
		}
		else if (index % 8 == 7) {
			if (index <= BOARD_SIZE - 2) this->saved_moves[index+1]  = false;
			if (index >= 7) this->saved_moves[index-7]  = false;
			if (index <= BOARD_SIZE - 10) this->saved_moves[index+9]  = false;
		}

		if( index/8 == 0 ){
			if (index >= 9) this->saved_moves[index-9]  =false;
			if (index >= 8) this->saved_moves[index-8]  =false;
			if (index >= 7) this->saved_moves[index-7]  =false;
		}
		else if (index/8 == 7) {
			if (index <= BOARD_SIZE - 8) this->saved_moves[index+7]  =false;
			if (index <= BOARD_SIZE - 9) this->saved_moves[index+8]  =false;
			if (index <= BOARD_SIZE - 10) this->saved_moves[index+9]  =false;
		}

		//check not to eat his king
		this->saved_moves[king] = false;

		//not to move into check
		if(index >= 9) this->saved_moves[index-9]  = saved_moves[index-9] && !reach[index-9];
		if(index >= 8) this->saved_moves[index-8]  = saved_moves[index-8] && !reach[index-8];
		if(index >= 7) this->saved_moves[index-7]  = saved_moves[index-7] && !reach[index-7];
		if(index >= 1) this->saved_moves[index-1]  = saved_moves[index-1] && !reach[index-1];
		if(index <= BOARD_SIZE-2) this->saved_moves[index+1]  = saved_moves[index+1] && !reach[index+1];
		if(index <= BOARD_SIZE-8) this->saved_moves[index+7]  = saved_moves[index+7] && !reach[index+7];
		if(index <= BOARD_SIZE-9) this->saved_moves[index+8]  = saved_moves[index+8] && !reach[index+8];
		if(index <= BOARD_SIZE-10) this->saved_moves[index+9]  = saved_moves[index+9] && !reach[index+9];

		//not to move into check by bishop (positions that are not in reach - "shadowed")
                QSharedPointer<Piece> bishop = this->his_player.toStrongRef()->get_piece('B');
                QVector<bool> b_reach;
		if(bishop != NULL){
			b_reach = bishop->reach();
		}
		if(bishop != NULL && b_reach[this->position->get_positon()] == true){
			if(this->position->same_falling_diagonal(bishop->position->get_positon())){
				if(index >= 7 && bishop->position->get_positon() != (index-7))
					this->saved_moves[index-7]  = false;
				if (index <= BOARD_SIZE - 8 && bishop->position->get_positon() != (index+7))
					this->saved_moves[index+7]  =false;
			}
			else if(this->position->same_raising_diagonal(bishop->position->get_positon())){
				if(index >= 9 && bishop->position->get_positon() != (index-9)) this->saved_moves[index-9]  = false;
				if (index <= BOARD_SIZE - 10 && bishop->position->get_positon() != (index+9)) this->saved_moves[index+9]  =false;
			}
		}

                //not move into check by queen (shadowed moves)
                QSharedPointer<Piece> queen = this->his_player.toStrongRef()->get_piece('Q');
                QVector<bool> q_reach;
                if(queen != NULL){
                        q_reach = queen->reach();
                }
                if(queen != NULL && q_reach[this->position->get_positon()] == true){
                        if(this->position->same_falling_diagonal(queen->position->get_positon())){
                                if(index >= 7 && queen->position->get_positon() != (index-7))
                                        this->saved_moves[index-7]  = false;
                                if (index <= BOARD_SIZE - 8 && queen->position->get_positon() != (index+7))
                                        this->saved_moves[index+7]  =false;
                        }
                        else if(this->position->same_raising_diagonal(queen->position->get_positon())){
                                if(index >= 9 && queen->position->get_positon() != (index-9)) this->saved_moves[index-9]  = false;
                                if (index <= BOARD_SIZE - 10 && queen->position->get_positon() != (index+9)) this->saved_moves[index+9]  =false;
                        }
                        else if(this->position->get_positon() / 8 == queen->position->get_positon() / 8){ //row
                                if(index % 8 != 0 && index-1 != queen->position->get_positon()) this->saved_moves[index-1] = false;
                                if(index % 8 != 7 && index+1 != queen->position->get_positon()) this->saved_moves[index+1] = false;
                        }
                        else if(this->position->get_positon() % 8 == queen->position->get_positon() % 8){ //column
                            if(index / 8 != 0 && index-8 != queen->position->get_positon()) this->saved_moves[index-8] = false;
                            if(index / 8 != 7 && index+8 != queen->position->get_positon()) this->saved_moves[index+8] = false;
                        }
                }

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
char King::short_name(){ return 'K'; }
