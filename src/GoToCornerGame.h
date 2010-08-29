/*
 * GoToCornerGame.h
 *
 *  Created on: 23.11.2009
 *      Author: slashrsm
 */

#ifndef GOTOCORNERGAME_H_
#define GOTOCORNERGAME_H_

#include <string>

#include "Game.h"
#include "Player.h"

using namespace std;

class GoToCornerGame: public Game {
    Q_OBJECT
private:
        QSharedPointer<Player> winner();
	bool game_ended();
	bool is_at_border();
	bool is_in_corner();
	bool is_in_corner_area();
//	bool white_lost_piece();

public:
        GoToCornerGame(QSharedPointer<Player>, QSharedPointer<Player>, int, int, QString, QString, bool, bool);
	virtual ~GoToCornerGame();
};


#endif /* GOTOCORNERGAME_H_ */
