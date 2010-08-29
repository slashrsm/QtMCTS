/*
 * Player.h
 *
 *  Created on: 1.8.2009
 *      Author: slashrsm
 */


#ifndef PLAYER_H_
#define PLAYER_H_

using namespace std;

#include <QtCore>

#include "Player.h"
#include "Position.h"
#include "Piece.h"

class Piece;

class Player : public QObject {
    Q_OBJECT

protected:

        QVector<bool> reach;
        QVector<bool> moves;
        QVector<bool> reach_minus_one;
        QVector<char> positions;
	void print_moves();
        QVector<QString> pgn_moves;
	char choose_random_move(int *, int);
	bool write_pgn;
	bool save_history;

public:
        QWeakPointer<Player> opponent;

	static int RANDOM_PLAYER;
	static int KBNK_WINNER_PLAYER;
	static int KBNK_LOOSER_PLAYER;

	//constructors
        Player(QSharedPointer< QVector< QSharedPointer<Piece> > >);
	virtual ~Player();
	virtual char move(int);
	char do_move(char, int);
        virtual void set_oponent(QSharedPointer<Player>);
        QVector<char> & where_are_pieces();
        QVector<bool> & my_reach();
        QVector<bool> & my_reach_minus_one(QSharedPointer<Piece>);
        QVector<bool> & my_moves();
        QSharedPointer<Piece> piece_at_pos(char);
	virtual void opponent_moved(char);
        QString get_pgn(int);
	int get_pgn_size();
	void clear_data();
        QSharedPointer<Piece> get_piece(char);
	void copy_situation();
	void restore_situation();
        void register_to_pieces(QSharedPointer<Player>);
        QSharedPointer<Player> duplicate(int);
        QList<char> & move_history();
        QList<int> & piece_history();

	//situation on chessboard (list of pieces)
        QSharedPointer< QVector< QSharedPointer<Piece> > > situation;
        QSharedPointer< QVector< QSharedPointer<Piece> > > situation_copy;
        QList<char> game_history_move;
        QList<int> game_history_piece;
};

#endif /* PLAYER_H_ */
