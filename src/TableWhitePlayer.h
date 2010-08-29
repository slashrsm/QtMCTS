/*
 * TableWhitePlayer.h
 *
 *  Created on: 30.5.2010
 *      Author: slashrsm
 */

#ifndef TABLEWHITEPLAYER_H_
#define TABLEWHITEPLAYER_H_

#include "Player.h"
#include "TableBase.h"

class TableWhitePlayer: public Player {
    Q_OBJECT
        QSharedPointer<TableBase> table_base;
public:
        TableWhitePlayer(QSharedPointer< QVector< QSharedPointer<Piece> > >);
	virtual ~TableWhitePlayer();
	char move(int);
        void set_oponent(QSharedPointer<Player>);

};

#endif /* TABLEWHITEPLAYER_H_ */
