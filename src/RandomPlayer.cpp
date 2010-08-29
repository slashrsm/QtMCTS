/*
 * RandomPlayer.cpp
 *
 *  Created on: 8.8.2009
 *      Author: slashrsm
 */

using namespace std;

#include <cstdlib>
#include <iostream>

#include "RandomPlayer.h"

/*
 * Constructors.
 */
RandomPlayer::RandomPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > > sit) : Player(sit) {}

RandomPlayer::~RandomPlayer() {}

/*
 * Sets opponent player.
 */
void RandomPlayer::set_oponent(QSharedPointer<Player> op){
	this->opponent = op;

	//register him
        for(int i=0; i<situation->size(); i++)
                this->situation->at(i)->his_player = this->opponent;
}

/*
 * Make a move.
 */
char RandomPlayer::move(int){
        int random = rand() % this->situation->size();
        QSharedPointer<Piece> piece = this->situation->at(random);
        QVector<char> list = piece->list_moves();
	while(list.size() == 0){
                random = rand() % this->situation->size();
                piece = this->situation->at(random);
		list = piece->list_moves();
	}
	int random1 = rand() % list.size();
	return this->do_move(list.at(random1), random);
}
