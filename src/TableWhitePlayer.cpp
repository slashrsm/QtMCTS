/*
 * TableWhitePlayer.cpp
 *
 *  Created on: 30.5.2010
 *      Author: slashrsm
 */

#include "TableWhitePlayer.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>

TableWhitePlayer::TableWhitePlayer(QSharedPointer< QVector< QSharedPointer<Piece> > > sit) : Player(sit){
        QSharedPointer<TableBase> tb(new TableBase("black_t.txt", true));
        this->table_base = tb;
}

TableWhitePlayer::~TableWhitePlayer() {}

char TableWhitePlayer::move(int){
        QVector<char> move = this->table_base->best_move(this->situation, this->opponent.toStrongRef()->situation);
	return this->do_move(move.at(1), move.at(0));
}

void TableWhitePlayer::set_oponent(QSharedPointer<Player> op){
	this->opponent = op;

	//register him
        for(int i=0; i<situation->size(); i++)
                this->situation->at(i)->his_player = this->opponent;
}
