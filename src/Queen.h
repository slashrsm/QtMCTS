/*
 * Queen.h
 *
 *  Created on: 26.8.2010
 *      Author: slashrsm
 */

#ifndef QUEEN_H
#define QUEEN_H

using namespace std;

#include "Piece.h"

class Queen: public Piece {
    Q_OBJECT
public:
        Queen(QSharedPointer<Position>, bool);
        ~Queen();
        QVector<bool> & reach();
        QVector<bool> & moves();
        char short_name();
};

#endif // QUEEN_H
