/*
 * RandomPlayer.h
 *
 *  Created on: 8.8.2009
 *      Author: slashrsm
 */

#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

using namespace std;

#include "Player.h"

class RandomPlayer: public Player {
    Q_OBJECT
public:
        RandomPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > >);
	virtual ~RandomPlayer();
	char move(int);
        void set_oponent(QSharedPointer<Player>);
};

#endif /* RANDOMPLAYER_H_ */
