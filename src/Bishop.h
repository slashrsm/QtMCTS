/*
 * Bishop.h
 *
 *  Created on: 8.8.2009
 *      Author: slashrsm
 */

#ifndef BISHOP_H_
#define BISHOP_H_

using namespace std;

#include "Piece.h"

class Bishop: public Piece {
    Q_OBJECT
public:
        Bishop(QSharedPointer<Position>, bool);
	~Bishop();
        QVector<bool> & reach();
        QVector<bool> & moves();
	char short_name();
};

#endif /* BISHOP_H_ */
