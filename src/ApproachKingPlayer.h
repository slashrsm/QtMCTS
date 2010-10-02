/*
 * ApproachKingPlayer.h
 *
 *  Created on: 16.8.2009
 *      Author: slashrsm
 */

#ifndef APPROACHKINGPLAYER_H_
#define APPROACHKINGPLAYER_H_

using namespace std;

#include "Player.h"

/*
 * Player that plays winner in MCTS simulations.
 * Heuristics:
 * 	1. Do not loose a piece.
 * 	2. With my king stay within distance 4 to his king.
 */
class ApproachKingPlayer: public Player {
    Q_OBJECT
public:
        ApproachKingPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > >);
        virtual ~ApproachKingPlayer();
	char move(int);
	bool is_safe(char, int);
        void set_oponent(QSharedPointer<Player>);
};

#endif /* APPROACHKINGPLAYER_H_ */
