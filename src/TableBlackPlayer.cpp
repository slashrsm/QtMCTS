/*
 * TableBlackPlayer.cpp
 *
 *  Created on: 29.5.2010
 *      Author: slashrsm
 */

#include "TableBlackPlayer.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>

TableBlackPlayer::TableBlackPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > > sit) : Player(sit){
        QSharedPointer<TableBase> tb(new TableBase("white_t.txt", false));
        this->table_base = tb;
}

TableBlackPlayer::~TableBlackPlayer() {}

char TableBlackPlayer::move(int){
	//take piece if possible
        QVector<bool> my_moves = this->my_moves();
        QVector<bool> his_reach = this->opponent.toStrongRef()->my_reach();
        QVector<char> his_pieces = this->opponent.toStrongRef()->where_are_pieces();
        for(int i=0; i<my_moves.size(); i++){
		if ( my_moves.at(i) && his_pieces.at(i) != '_' && !his_reach.at(i))
			return this->do_move(i,0);

	}

        QVector<char> move = this->table_base->best_move(this->situation, this->opponent.toStrongRef()->situation);
	return this->do_move(move.at(1), move.at(0));
}

void TableBlackPlayer::set_oponent(QSharedPointer<Player> op){
        this->opponent = op;

	//register him
        for(int i=0; i<situation->size(); i++)
                this->situation->at(i)->his_player = this->opponent;
}
