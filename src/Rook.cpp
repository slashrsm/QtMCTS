/*
 * Rook.cpp
 *
 *  Created on: 26.8.2010
 *      Author: slashrsm
 */

using namespace std;

#include <cstring>
#include <iostream>

#include "environment.h"
#include "Rook.h"

Rook::Rook(QSharedPointer<Player> my, QSharedPointer<Player> his, QSharedPointer<Position> pos, bool white) : Piece(my, his, pos, white)  {}

Rook::~Rook(){}

/*
 * Calculates reach.
 */
QVector<bool> & Rook::reach(){
        if(this->saved_reach.empty()){

                QVector<char> where_my = this->my_player.toStrongRef()->where_are_pieces();
                QVector<char> where_his = this->his_player.toStrongRef()->where_are_pieces();
                this->saved_reach.fill(false,BOARD_SIZE);
                char index = this->position->get_positon();
                char iter = index;
                char iter_before = index;

                //row to the left
                if(index % 8 != 0){
                    iter = index-1;
                    iter_before = index;
                        while(iter >= 0 && iter < BOARD_SIZE && index / 8 == iter / 8 && (where_my[iter_before] == '_' || iter_before == index) && where_his[iter_before] == '_'){
                            this->saved_reach[iter] = true;
                            iter_before = iter;
                            iter--;
                        }
                }

                //row to the right
                if(index % 8 != 7){
                    iter = index+1;
                    iter_before = index;
                        while(iter >= 0 && iter < BOARD_SIZE && index / 8 == iter / 8 && (where_my[iter_before] == '_' || iter_before == index) && where_his[iter_before] == '_'){
                            this->saved_reach[iter] = true;
                            iter_before = iter;
                            iter++;
                        }
                }


                //column to the top
                if(index / 8 != 7){
                    iter = index+8;
                    iter_before = index;
                        while(iter >= 0 && iter < BOARD_SIZE && (where_my[iter_before] == '_' || iter_before == index) && where_his[iter_before] == '_'){
                            this->saved_reach[iter] = true;
                            iter_before = iter;
                            iter += 8;
                        }
                }

                //column to the bottom
                if(index / 8 != 0){
                    iter = index-8;
                    iter_before = index;
                        while(iter >= 0 && iter < BOARD_SIZE && (where_my[iter_before] == '_' || iter_before == index) && where_his[iter_before] == '_'){
                            this->saved_reach[iter] = true;
                            iter_before = iter;
                            iter -= 8;
                        }
                }

                //debug output
                if(PRINT_REACH){
                        cout << "Rook: " << endl;
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
QVector<bool>& Rook::moves(){
        if (this->saved_moves.empty()) {
            QVector<char> where_my = this->my_player.toStrongRef()->where_are_pieces();
            QVector<char> where_his = this->his_player.toStrongRef()->where_are_pieces();
            this->saved_moves.fill(false,64);
            char index = this->position->get_positon();
            char iter = index;
            char iter_before = index;
            char king = this->his_player.toStrongRef()->situation->at(0)->position->get_positon();

                //row to the left
                if(index % 8 != 0){
                    iter = index-1;
                    iter_before = index;
                        while(iter >= 0 && iter < BOARD_SIZE && index / 8 == iter / 8 && (where_my[iter_before] == '_' || iter_before == index) && where_his[iter_before] == '_'){
                            this->saved_moves[iter] = where_my[iter] == '_' ? true : false;
                            iter_before = iter;
                            iter--;
                        }
                }

                //row to the right
                if(index % 8 != 7){
                    iter = index+1;
                    iter_before = index;
                        while(iter >= 0 && iter < BOARD_SIZE && index / 8 == iter / 8 && (where_my[iter_before] == '_' || iter_before == index) && where_his[iter_before] == '_'){
                            this->saved_moves[iter] = where_my[iter] == '_' ? true : false;
                            iter_before = iter;
                            iter++;
                        }
                }


                //column to the top
                if(index / 8 != 7){
                    iter = index+8;
                    iter_before = index;
                        while(iter >= 0 && iter < BOARD_SIZE && (where_my[iter_before] == '_' || iter_before == index) && where_his[iter_before] == '_'){
                            this->saved_moves[iter] = where_my[iter] == '_' ? true : false;
                            iter_before = iter;
                            iter += 8;
                        }
                }

                //column to the bottom
                if(index / 8 != 0){
                    iter = index-8;
                    iter_before = index;
                        while(iter >= 0 && iter < BOARD_SIZE && (where_my[iter_before] == '_' || iter_before == index) && where_his[iter_before] == '_'){
                            this->saved_moves[iter] = where_my[iter] == '_' ? true : false;
                            iter_before = iter;
                            iter -= 8;
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
char Rook::short_name(){ return 'R'; }


