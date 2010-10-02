/*
 * King.h
 *
 *  Created on: 1.8.2009
 *      Author: slashrsm
 */

#ifndef KING_H_
#define KING_H_

using namespace std;

#include "Piece.h"

class King: public Piece {
    Q_OBJECT
public:
        King(QSharedPointer<Position>, bool);
	~King();
        QVector<bool> & reach();
        QVector<bool> & moves();
	char short_name();
};

#endif /* KING_H_ */
