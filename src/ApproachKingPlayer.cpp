/*
 * ApproachKingPlayer.cpp
 *
 *  Created on: 16.8.2009
 *      Author: slashrsm
 */

using namespace std;

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>

#include "ApproachKingPlayer.h"

/*
 * Constructors.
 */
ApproachKingPlayer::ApproachKingPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > > sit) : Player(sit) {}

ApproachKingPlayer::~ApproachKingPlayer() {}

/*
 * Sets opponent player.
 */
void ApproachKingPlayer::set_oponent(QSharedPointer<Player> op){
	this->opponent = op;

	//register him
        for(int i=0; i<situation->size(); i++)
                this->situation->at(i)->his_player = this->opponent;
}

/*
 * Play move. Heuristics:
 * 	1. Do not loose a piece.
 * 	2. With my king stay within distance 4 to his king.
 */
char ApproachKingPlayer::move(int){
	//weights
	int dangerous_position = 0;
//	int within_distance = 20;
	int go_closer_tresshold = 50;
	int other = 1;

	//check if my piece is attacked
        QVector<bool> his_reach = this->opponent.toStrongRef()->my_reach();
        QVector<bool> my_reach = this->my_reach();
        QSharedPointer<Piece> curr;
	int in_danger = -1;
        for (int i=0; i < situation->size(); ++i) {
                curr = situation->at(i);
		if( his_reach[curr->position->get_positon()] && !my_reach[curr->position->get_positon()]){
			in_danger = i;
			break;
		}
	}

	//if found piece in danger move it, if not check for kings distance
	char move = -1;
	int piece = -1;
	if( in_danger != -1){
		//find safe move
		piece = in_danger;
                QVector<char> moves = situation->at(piece)->list_moves();
		int points[moves.size()];
		char new_pos = -1;
                for (int i=0; i < moves.size(); ++i) {
			new_pos = moves[i];
			if(!is_safe(new_pos,piece))
				points[i] = dangerous_position;
			else
				points[i] = other;
		}

		move = this->choose_random_move(points, piece);
	}
	else{
//		//randomly choose piece
//		piece = rand() % this->situation->size();
//		Piece * p = this->situation->at(piece);
//		vector<char> moves = p->list_moves();
//		while(moves.size() == 0){
//			piece = rand() % this->situation->size();
//			p = this->situation->at(piece);
//			moves = p->list_moves();
//		}
//
//		//calculate points
//		int points[moves.size()];
//		char new_pos = -1;
//		for (int i = 0; i < moves.size(); ++i) {
//			new_pos = moves[i];
//			if(piece == 0 && p->mdistance_to_piece(this->opponent->situation->at(0)) <= 4)
//				points[i] = within_distance;
//			else if(!is_safe(new_pos,piece))
//				points[i] = dangerous_position;
//			else
//				points[i] = other;
//		}
//
//		move = this->choose_random_move(points, piece);

                QSharedPointer<Piece> king = this->situation->at(0);
                QVector<char> approach_king_for_2;
                QVector<char> approach_king_for_1;

		char curr_move = -1, after, before, diff;
                QVector<char> king_moves = king->list_moves();
                for (int i=0; i < king_moves.size(); ++i) {
			curr_move = king_moves[i];
                        before = king->mdistance_to_piece(this->opponent.toStrongRef()->situation->at(0));
                        after = this->opponent.toStrongRef()->situation->at(0)->mdistance_to_pos(curr_move);
//			cout << (int)before << " -> " << (int)after << endl;
			if(before >= 4 && before > after){
				diff = before-after;
				if(diff == 2)
					approach_king_for_2.push_back(curr_move);
				else
					approach_king_for_1.push_back(curr_move);
			}
		}

		if(approach_king_for_2.size() > 0 && (rand() % 100) < go_closer_tresshold){  //Just to ensure that also other moves are checked in MCTS
			piece = 0;
			move = approach_king_for_2.at(rand() % approach_king_for_2.size());
		}
		else if(approach_king_for_1.size() > 0 && (rand() % 100) < go_closer_tresshold){ //Just to ensure that also other moves are checked in MCTS
			piece = 0;
			move = approach_king_for_1.at(rand() % approach_king_for_1.size());
		}
		else{
                        piece = rand() % this->situation->size();
                        QSharedPointer<Piece> p = this->situation->at(piece);
                        QVector<char> list = p->list_moves();
			int sz = list.size();
			while(list.size() == 0){
                                piece = rand() % this->situation->size();
                                QSharedPointer<Piece> p = this->situation->at(piece);
				list = p->list_moves();
				sz = list.size();
			}

			move = list.at(rand() % list.size());
			//prevent king from going away of his king
                        before = king->mdistance_to_piece(this->opponent.toStrongRef()->situation->at(0));
                        after = this->opponent.toStrongRef()->situation->at(0)->mdistance_to_pos(move);
			int count = 0;		//if all moves go back we must prevent inf. loop
			while(piece == 0 && after > before && count < 50 && list.size() == 0){
                                piece = rand() % this->situation->size();
                                p = this->situation->at(piece);

				list = p->list_moves();
				if(list.size() == 0) break;

				move = list.at(rand() % list.size());
                                before = king->mdistance_to_piece(this->opponent.toStrongRef()->situation->at(0));
                                after = this->opponent.toStrongRef()->situation->at(0)->mdistance_to_pos(move);
				count++;
			}

		}

 	}

	return do_move(move,piece);
}

/*
 * Checks if new position is safe.
 */
bool ApproachKingPlayer::is_safe(char pos, int piece){
        QVector<bool> my_small_reach = this->my_reach_minus_one(situation->at(piece));
        QVector<bool> his_reach = this->opponent.toStrongRef()->my_reach();

	return !his_reach[pos] || (his_reach[pos] && my_small_reach[pos]);
}
