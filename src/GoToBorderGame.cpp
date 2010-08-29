/*
 * GoToBorderGame.cpp
 *
 *  Created on: 6.9.2009
 *      Author: slashrsm
 */

using namespace std;

#include <string>

#include "GoToBorderGame.h"
#include "Game.h"
#include "Player.h"

/*
 * Constructors
 */
GoToBorderGame::GoToBorderGame(QSharedPointer<Player> white, QSharedPointer<Player> black, int maxmoves=100, int timelimit=10, QString event="", QString pgn="", bool black_on_turn=false, bool simulation=false) : Game(white, black, maxmoves, timelimit, event, pgn, black_on_turn, simulation) {
}

GoToBorderGame::~GoToBorderGame() {}

/*
 * Tests if game ended.
 */
bool GoToBorderGame::game_ended(){ return this->is_at_border() || this->white_lost_piece() || this->cannot_move(); }

/*
 * Returns winner.
 */
QSharedPointer<Player> GoToBorderGame::winner(){
        QSharedPointer<Player> winner;
        if (this->white->situation->size() < 3) //white lost piece
		winner = this->black;
	else if (is_stalemate())  //stalemate
		winner = this->black;
	else if (is_checkmate()) //checkmate
		winner = this->white;
	else if (is_at_border())
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
bool GoToBorderGame::is_at_border(){
//	int size = this->black->situation->size();
        QVector<char> coords = this->black->situation->at(0)->position->get_coords();
        return coords[0] == 0 || coords[0] == 7 || coords[1] == 0 || coords[1] == 7;
}

