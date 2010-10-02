#ifndef TOCENTERPLAYER_H
#define TOCENTERPLAYER_H

using namespace std;

#include <QSharedPointer>
#include "Player.h"


/*
 * Pseudo random player that plays "looser" in KQK ending.
 * Heuristics:
 * 1. Stay close to centre.
 */
class ToCenterPlayer: public Player {
    Q_OBJECT
public:
        ToCenterPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > > sit);
        virtual ~ToCenterPlayer();
        char move(int);
        char distance_to_center(char);
        char pos_dist(char,char);
        void set_oponent(QSharedPointer<Player>);
};

#endif // TOCENTERPLAYER_H
