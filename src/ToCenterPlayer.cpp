/*
 * ToCenterPlayer.cpp
 *
 * Black player (King) in KQK ending. It plays with simple heuristics:
 *  1. Take opponent's piece if possible
 *  2. Go closer to center if possible
 *  3. Stay on same distance from center if possible
 *  4. Do anything else
 *
 *
 *  Created on: 30.9.2010
 *      Author: slashrsm
 */

using namespace std;

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "ToCenterPlayer.h"
#include "King.h"


ToCenterPlayer::ToCenterPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > > sit) : Player(sit)  {}
ToCenterPlayer::~ToCenterPlayer() {}

/*
 * Sets opponent player.
 */
void ToCenterPlayer::set_oponent(QSharedPointer<Player> op){
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
 */
char ToCenterPlayer::move(int){
        //king
        QSharedPointer<Piece> king = this->situation->at(0);
        QVector<char> moves = king->list_moves();
        char curr_m_dist = this->distance_to_center(king->position->get_positon());

        vector<char> take_a_piece;
        vector<char> go_to_center;
        vector<char> stay_on_distance;
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
                else
                        other_move.insert(other_move.end(),move);
        }

        if (take_a_piece.size() != 0)
                move = take_a_piece[rand() % take_a_piece.size()];

        else if (go_to_center.size() != 0)
                move = go_to_center[rand() % go_to_center.size()];

        else if (stay_on_distance.size() != 0)
                move = stay_on_distance[rand() % stay_on_distance.size()];

        else
                move = other_move[rand() % other_move.size()];

        return this->do_move(move,0);
}

/*
 * Calculates distance to board center.
 */
char ToCenterPlayer::distance_to_center(char pos){
        int x = pos % 8;
        int y = pos / 8;

        return max(min(abs(x-3),abs(x-4)),min(abs(y-3),abs(y-4)));
}

/*
 * Returns distance between two positions.
 */
char ToCenterPlayer::pos_dist(char start, char end){
        char x1 = start % 8;
        char y1 = start / 8;
        char x2 = end % 8;
        char y2 = end / 8;

        return abs(x1-x2) + abs(y1-y2);
}
