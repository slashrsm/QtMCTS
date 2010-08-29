/*
 * GoToCornerDirectGame.h
 *
 *  Created on: 24.11.2009
 *      Author: slashrsm
 */

#ifndef GOTOCORNERDIRECTGAME_H_
#define GOTOCORNERDIRECTGAME_H_

#include <string>

#include "Game.h"
#include "Player.h"

using namespace std;

class GoToCornerDirectGame: public Game {
    Q_OBJECT
private:
        QSharedPointer<Player> winner();
	bool game_ended();
	bool is_in_corner();
	bool is_in_corner_area();
//	bool white_lost_piece();


public:
        GoToCornerDirectGame(QSharedPointer<Player>, QSharedPointer<Player>, int, int, QString, QString, bool, bool);
	virtual ~GoToCornerDirectGame();
};

#endif /* GOTOCORNERDIRECTGAME_H_ */
