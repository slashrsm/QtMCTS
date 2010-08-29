/*
 * GoToBorderGame.h
 *
 *  Created on: 6.9.2009
 *      Author: slashrsm
 */

#ifndef GOTOBORDERGAME_H_
#define GOTOBORDERGAME_H_

using namespace std;

#include <string>

#include "Game.h"
#include "Player.h"

class GoToBorderGame: public Game {
    Q_OBJECT
private:
        QSharedPointer<Player> winner();
	bool game_ended();
	bool is_at_border();

public:
        GoToBorderGame(QSharedPointer<Player>, QSharedPointer<Player>, int, int, QString, QString, bool, bool);
	virtual ~GoToBorderGame();
};

#endif /* GOTOBORDERGAME_H_ */
