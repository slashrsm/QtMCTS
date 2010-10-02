/*
 * Game.h
 *
 *  Created on: 1.8.2009
 *      Author: slashrsm
 */

#ifndef GAME_H_
#define GAME_H_

using namespace std;

#include "Player.h"
#include <QSharedPointer>


class Game : public QObject {
    Q_OBJECT
protected:
        virtual QSharedPointer<Player> winner();
	virtual bool game_ended();
	bool is_checkmate();
	bool is_check();
	bool cannot_move();
        bool white_lost_piece();
	bool is_stalemate();
        bool is_in_corner();
	void print_situation();
	void generate_fen();

        QSharedPointer<Player> white;
        QSharedPointer<Player> black;
        QSharedPointer<Player> on_move;
        QSharedPointer<Player> on_hold;
	int maxmoves;
	int timelimit;
        QString event;
        QString pgn;
        QString white_situation;
        QString black_situation;
        QString fen;
        QString result;
	bool black_on_turn;
	bool simulation;
	int moves;

public:
	static int GO_TO_BORDER;
	static int GO_TO_CORNER;
	static int GO_TO_CORNER_DIRECT;
	static int GO_TO_CHECKMATE;
        static int WHITE_START_PIECE_COUNT;
        static int BLACK_START_PIECE_COUNT;

        Game(QSharedPointer<Player>, QSharedPointer<Player>, int, int, QString, QString, bool, bool);
	virtual ~Game();
        QSharedPointer<Player> play();
	void write_pgn();

};

#endif /* GAME_H_ */
