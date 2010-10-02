/*
 * Piece.h
 *
 *  Created on: 1.8.2009
 *      Author: Janez Urevc [63040171]
 */

#ifndef PIECE_H_
#define PIECE_H_

using namespace std;

#include <vector>
#include "Player.h"
#include "Position.h"

class Player;
class Position;
class Piece;

class Piece : public QObject {
    Q_OBJECT
	protected:

                QVector<bool> saved_reach;
                QVector<bool> saved_moves;
                QVector<char> saved_list_moves;
                void print_array(QVector<bool> &);

	public:
                static QSharedPointer<Player> dummy();
		bool white;
                Piece(QSharedPointer<Position>, bool);
		virtual ~Piece();
//		virtual bool is_valid(char);
		virtual char short_name();
		bool move(char);
                virtual QVector<bool>& reach();
                virtual QVector<bool>& moves();
		char mdistance_to_pos(char);
                char mdistance_to_piece(QSharedPointer<Piece>);
		void print_reach();
		void print_moves();
                void print_array(QVector<char> &);
		void clear_data();
                QVector<char> & list_moves();
                QSharedPointer<Position> position;
                virtual QSharedPointer<Piece> duplicate();
                QWeakPointer<Player> my_player;
                QWeakPointer<Player> his_player;
};

#endif /* PIECE_H_ */
