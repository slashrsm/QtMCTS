/*
 * KBNKWinnerPlayer.h
 *
 *  Created on: 16.8.2009
 *      Author: slashrsm
 */

#ifndef KBNKWINNERPLAYER_H_
#define KBNKWINNERPLAYER_H_

using namespace std;

#include "Player.h"

/*
 * Player that plays winner in MCTS simulations.
 * Heuristics:
 * 	1. Do not loose a piece.
 * 	2. With my king stay within distance 4 to his king.
 */
class KBNKWinnerPlayer: public Player {
    Q_OBJECT
public:
        KBNKWinnerPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > >);
	virtual ~KBNKWinnerPlayer();
	char move(int);
	bool is_safe(char, int);
        void set_oponent(QSharedPointer<Player>);
};

#endif /* KBNKWINNERPLAYER_H_ */
