/*
 * GoToCornerGame.cpp
 *
 *  Created on: 23.11.2009
 *      Author: slashrsm
 */

using namespace std;

#include <string>

#include "GoToCornerGame.h"
#include "Game.h"
#include "Player.h"

/*
 * Constructors
 */
GoToCornerGame::GoToCornerGame(QSharedPointer<Player> white, QSharedPointer<Player> black, int maxmoves=100, int timelimit=10, QString event="", QString pgn="", bool black_on_turn=false, bool simulation=false) : Game(white, black, maxmoves, timelimit, event, pgn, black_on_turn, simulation) {
}

GoToCornerGame::~GoToCornerGame() {}

/*
 * Tests if game ended.
 */
bool GoToCornerGame::game_ended(){ return !this->is_at_border() || this->is_in_corner() || this->white_lost_piece() || this->cannot_move(); }

/*
 * Returns winner.
 */
QSharedPointer<Player> GoToCornerGame::winner(){
//	if (!this->is_at_border() || this->white->situation->size() < 3)
//		return this->black;
//	else if (is_stalemate())
//		return this->black;
//	else if (is_checkmate())
//		return this->white;
//	else if (is_in_corner())
//		return this->white;
//	else
//		return this->black;

        QSharedPointer<Player> winner;
        if (this->white->situation->size() < 3) //white lost piece
		winner = this->black;
	else if (is_stalemate())  //stalemate
		winner = this->black;
	else if (is_checkmate()) //checkmate
		winner = this->white;
	else if (is_in_corner())
		winner = this->white;
	else
                winner.clear();

	if(winner == NULL)
                this->result += "1/2-1/2";
	else if (winner == this->white)
                this->result += "1-0";
	else if (winner == this->black)
                this->result += "0-1";

	return winner;
}

/*
 * Checks if black king is at border.
 */
bool GoToCornerGame::is_at_border(){
//	int size = this->black->situation->size();
        QVector<char> coords = this->black->situation->at(0)->position->get_coords();
	bool ret = coords[0] == 0 || coords[0] == 7 || coords[1] == 0 || coords[1] == 7;
	return ret;
}


/*
 * Checks if black king is in right corner.
 */
bool GoToCornerGame::is_in_corner(){
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

/**
 * Check if king is in right corner + 1 positon around.
 */
bool GoToCornerGame::is_in_corner_area(){
        QSharedPointer<Piece> his_king = this->black->situation->at(0);
	bool ret = his_king->mdistance_to_pos(0) < 2 || his_king->mdistance_to_pos(7) < 2;
	ret |= his_king->mdistance_to_pos(56) < 2 || his_king->mdistance_to_pos(63) < 2;
	if(ret){
                QSharedPointer<Piece> p;
                for(int i=0; i<this->white->situation->size(); i++){
                        p = this->white->situation->at(i);
			if(p->short_name() == 'B')
				break;
		}

		char bishop_color = p->position->get_color();
		if(bishop_color == 'B' && (his_king->mdistance_to_pos(56) < 2 || his_king->mdistance_to_pos(7) < 2))
			ret = false;
		else if(bishop_color == 'W' && (his_king->mdistance_to_pos(0) < 2 || his_king->mdistance_to_pos(63) < 2))
			ret = false;
	}
	return ret;
}

///*
// * Checks if white still has 3 pieces.
// */
//bool GoToCornerGame::white_lost_piece(){ return this->white->situation->size() < 3; }
