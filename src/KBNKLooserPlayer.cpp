/*
 * KBNKLooserPlayer.cpp
 *
 * Black player (King) in KBNK ending. It plays with simple heuristics:
 *  1. Take opponent's piece if possible
 *  2. Go closer to center if possible
 *  3. Stay on same distance from center if possible
 *  4. Do anything else
 *
 * Idea: at some stage could be reasonable to add another heuristics:
 *  - after line 3. add "go to wrong corner"
 *
 *  Created on: 14.8.2009
 *      Author: slashrsm
 */

using namespace std;

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "KBNKLooserPlayer.h"
#include "King.h"

KBNKLooserPlayer::KBNKLooserPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > > sit) : Player(sit)  {}
KBNKLooserPlayer::~KBNKLooserPlayer() {}

/*
 * Sets opponent player.
 */
void KBNKLooserPlayer::set_oponent(QSharedPointer<Player> op){
	this->opponent = op;

	//register him
        for(int i=0; i<situation->size(); i++)
                this->situation->at(i)->his_player = this->opponent;
}

/*
 * Plays a move.
 *
 * Heuristics:
 * 	1. Smaller or same distance to center
 * 	2. Smaller or same distance to wrong corner
 */
char KBNKLooserPlayer::move(int){
	//weights
//	int closer_to_center = 100;
//	int closer_to_corner = 0;
//	int other = 1;

	//king
        QSharedPointer<Piece> king = this->situation->at(0);
        QVector<char> moves = king->list_moves();
	char curr_m_dist = this->distance_to_center(king->position->get_positon());
    char curr_safe_dist = this->safe_corner_dist(king->position->get_positon());

	//opponent bishop
//	ptr_Piece bishop = this->opponent->get_piece('B');
//	char curr_corner_dist=-1, corner_to_go=-1;
//	if(bishop != NULL){
//		char bishop_pos = bishop->position->get_positon();
//		char bishop_x = bishop_pos % 8;
//		char bishop_y = bishop_pos /8;
//		char op_corner = abs(bishop_x-bishop_y) % 2;
//		if(op_corner == 0){
//			if(this->pos_dist(king->position->get_positon(),7) <= this->pos_dist(king->position->get_positon(),56))
//				corner_to_go = 7;
//			else
//				corner_to_go = 56;
//		}
//		else {
//			if(this->pos_dist(king->position->get_positon(),0) <= this->pos_dist(king->position->get_positon(),63))
//				corner_to_go = 0;
//			else
//				corner_to_go = 63;
//		}
//		curr_corner_dist = this->pos_dist(king->position->get_positon(),corner_to_go);
//	}

//	//init variables
//	int points[moves.size()];
//
//	//calculate points for all moves
//	char move = -1;
//	for (int i = 0; i < moves.size(); ++i) {
//		move = moves[i];
//		if (this->distance_to_center(move) <= curr_m_dist)
//			points[i] = closer_to_center;
//		else if (corner_to_go != -1 && this->pos_dist(move,corner_to_go) <= curr_corner_dist)
//			points[i] = closer_to_corner;
//		else
//			points[i] = other;
//	}
//	return this->do_move(this->choose_random_move(points,0),0);

	
	vector<char> take_a_piece;
	vector<char> go_to_center;
	vector<char> stay_on_distance;
        vector<char> go_to_safe_corner;
	vector<char> other_move;
	char move = -1;
        for (int i=0; i < moves.size(); ++i) {
		move = moves[i];

                // Player heuristics
                if(this->opponent.toStrongRef()->where_are_pieces().at(move) != '_' &&
                        !this->opponent.toStrongRef()->my_reach().at(move))
			take_a_piece.insert(take_a_piece.end(),move);
		else if (this->distance_to_center(move) < curr_m_dist && this->distance_to_center(move) < 3) //TODO WARNING: drugi del pogoja - da preprečimo napačno gibanje ob robu BO??
			go_to_center.insert(go_to_center.end(),move);
		else if (this->distance_to_center(move) == curr_m_dist)
			stay_on_distance.insert(stay_on_distance.end(),move);
                else if (this->safe_corner_dist(move) < curr_safe_dist)
                    	go_to_safe_corner.insert(go_to_safe_corner.end(),move);
		else
			other_move.insert(other_move.end(),move);
	}

	if (take_a_piece.size() != 0)
		move = take_a_piece[rand() % take_a_piece.size()];

        else if (go_to_center.size() != 0)
		move = go_to_center[rand() % go_to_center.size()];

        else if (stay_on_distance.size() != 0)
		move = stay_on_distance[rand() % stay_on_distance.size()];

        else if (go_to_safe_corner.size() != 0)
                move = go_to_safe_corner[rand() % go_to_safe_corner.size()];

        else
		move = other_move[rand() % other_move.size()];

	return this->do_move(move,0);
}

/*
 * Calculates distance to board center.
 */
char KBNKLooserPlayer::distance_to_center(char pos){
	int x = pos % 8;
	int y = pos / 8;

//	return min(abs(x-4),abs(x-5)) + min(abs(y-4),abs(y-5));
	return max(min(abs(x-3),abs(x-4)),min(abs(y-3),abs(y-4)));
}

/*
 * Returns distance between two positions.
 */
char KBNKLooserPlayer::pos_dist(char start, char end){
	char x1 = start % 8;
	char y1 = start / 8;
	char x2 = end % 8;
	char y2 = end / 8;

	return abs(x1-x2) + abs(y1-y2);
}

/*
 * Returns distance to closest safe corner.
 */
char KBNKLooserPlayer::safe_corner_dist(char pos){
    // Find his Bishop
    QSharedPointer<Piece> op_bishop;
    for (int i=0; i < this->opponent.toStrongRef()->situation->size(); i++)
        if (this->opponent.toStrongRef()->situation->at(i)->short_name() == 'B')
            op_bishop = this->opponent.toStrongRef()->situation->at(i);


    // Calculate distances to safe corners
    char dist = -1;
    if (op_bishop != NULL){
        char bishop_color = op_bishop->position->get_color();
        if (bishop_color == 'W'){
            char dist_0 = this->pos_dist(pos,0);
            char dist_63 = this->pos_dist(pos,63);
            dist = dist_0 < dist_63 ? dist_0 : dist_63;
        }
        else {
            char dist_7 = this->pos_dist(pos,7);
            char dist_56 = this->pos_dist(pos,56);
            dist = dist_7 < dist_56 ? dist_7 : dist_56;
        }
    }

    // DEBUG WARNING: Check if distance was found
    if (dist == -1){
//        cout << "[KBNKLooserPlayer.cpp:safe_corner_dist()] - Distance was not found! Exiting..." << endl;
        dist = 255;
    }

    return dist;
}
