/*
 * TableBlackPlayer.h
 *
 *  Created on: 29.5.2010
 *      Author: slashrsm
 */

#ifndef TABLEBLACKPLAYER_H_
#define TABLEBLACKPLAYER_H_
#include "Player.h"
#include "TableBase.h"

class TableBlackPlayer: public Player {
    Q_OBJECT
        QSharedPointer<TableBase> table_base;
public:
        TableBlackPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > >);
	virtual ~TableBlackPlayer();
	char move(int);
        void set_oponent(QSharedPointer<Player>);

};

#endif /* TABLEBLACKPLAYER_H_ */
