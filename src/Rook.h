/*
 * Rook.h
 *
 *  Created on: 30.8.2010
 *      Author: slashrsm
 */


#ifndef ROOK_H
#define ROOK_H

using namespace std;

#include "Piece.h"

class Rook: public Piece {
    Q_OBJECT
public:
        Rook(QSharedPointer<Player>, QSharedPointer<Player>, QSharedPointer<Position>, bool);
        ~Rook();
        QVector<bool> & reach();
        QVector<bool> & moves();
        char short_name();
};


#endif // ROOK_H
