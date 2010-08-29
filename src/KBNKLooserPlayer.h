/*
 * KBNKLooserPlayer.h
 *
 *  Created on: 14.8.2009
 *      Author: slashrsm
 */

#ifndef KBNKLOOSERPLAYER_H_
#define KBNKLOOSERPLAYER_H_

using namespace std;

#include <QSharedPointer>
#include "Player.h"


/*
 * Pseudo random player that plays "looser" in KBNK ending.
 * Heuristics:
 * 1. Stay close to centre.
 * 2. Stay close to wrong corner.
 */
class KBNKLooserPlayer: public Player {
    Q_OBJECT
public:
        KBNKLooserPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > > sit);
	virtual ~KBNKLooserPlayer();
	char move(int);
	char distance_to_center(char);
	char pos_dist(char,char);
        char safe_corner_dist(char);
        void set_oponent(QSharedPointer<Player>);
};

#endif /* KBNKLOOSERPLAYER_H_ */
