#ifndef KQKLOOSERPLAYER_H
#define KQKLOOSERPLAYER_H

using namespace std;

#include <QSharedPointer>
#include "Player.h"


/*
 * Pseudo random player that plays "looser" in KQK ending.
 * Heuristics:
 * 1. Stay close to centre.
 */
class KQKLooserPlayer: public Player {
    Q_OBJECT
public:
        KQKLooserPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > > sit);
        virtual ~KQKLooserPlayer();
        char move(int);
        char distance_to_center(char);
        char pos_dist(char,char);
        void set_oponent(QSharedPointer<Player>);
};

#endif // KQKLOOSERPLAYER_H
