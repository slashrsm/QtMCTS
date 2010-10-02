/*
 * Knight.h
 *
 *  Created on: 8.8.2009
 *      Author: slashrsm
 */

#ifndef KNIGHT_H_
#define KNIGHT_H_

using namespace std;

#include "Piece.h"

class Knight: public Piece {
    Q_OBJECT
public:
        Knight(QSharedPointer<Position>, bool);
	~Knight();
        QVector<bool> & reach();
        QVector<bool> & moves();
	char short_name();
};

#endif /* KNIGHT_H_ */
