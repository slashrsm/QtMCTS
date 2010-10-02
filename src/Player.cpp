/*
 * Player.cpp
 *
 *  Created on: 1.8.2009
 *      Author: slashrsm
 */

using namespace std;

#define BOARD_SIZE 64

#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "environment.h"
#include "Player.h"
#include "Position.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "RandomPlayer.h"
#include "KBNKLooserPlayer.h"
#include "ApproachKingPlayer.h"
#include "MCTSPlayer.h"
#include "ToCenterPlayer.h"

/*
 * Static members.
 */
int Player::RANDOM_PLAYER = 0;
int Player::MCTS_PLAYER = 1;
int Player::TABLEBASE_PLAYER = 2;
int Player::TO_CENTER_PLAYER = 3;
int Player::APPROACH_KING_PLAYER = 4;
int Player::KBNK_LOOSER_PLAYER = 5;

Player::Player(QSharedPointer< QVector< QSharedPointer<Piece> > > sit) {
	this->situation = sit;
        QSharedPointer< QVector< QSharedPointer<Piece> > > sit_c(new QVector< QSharedPointer<Piece> >());
        this->situation_copy = sit_c;
	this->write_pgn = true;
	this->save_history = true;
}

Player::~Player() {
//	this->situation->clear();
//	this->situation_copy->clear();
}

/*
 * Register player to pieces.
 */
void Player::register_to_pieces(QSharedPointer<Player> me){
    for(int i=0; i<situation->size(); i++)
            this->situation->at(i)->my_player = me;
}

/*
 * Sets opponent player.
 */
void Player::set_oponent(QSharedPointer<Player> op){
        this->opponent = op;

	//register him
        for(int i=0; i<situation->size(); i++)
                this->situation->at(i)->his_player = this->opponent;
}

/*
 * Plays a move.
 */
char Player::move(int){ return -1; }

/*
 * Actually takes a move and other things that need to be done.
 */
char Player::do_move(char m, int p){
        QSharedPointer<Piece> piece = this->situation->at(p);

        if(!this->situation->at(p)->moves().at(m)){
                for(int i=0; i< this->situation->size(); i++)
                        cout << this->situation->at(i)->short_name() << " at " << (int) this->situation->at(i)->position->get_positon() << endl;

                qDebug() << "Piece: " << p;
                qDebug() << "Move: " << (int)m;


                qDebug() << "[Player::do_move]Kurac to!";

	}

        piece->move(m);

	if(write_pgn){
            char c = piece->short_name();
                QString pgn(c);
                pgn += piece->position->get_notation();

		this->pgn_moves.push_back(pgn);
	}

	if(save_history){
		this->game_history_move.push_front(m);
		this->game_history_piece.push_front(p);
	}

	this->clear_data();
        this->opponent.toStrongRef()->clear_data();

	return m;
}

/*
 * Clears saved data.
 */
void Player::clear_data(){
	this->moves.erase(moves.begin(),moves.end());
	this->reach.erase(reach.begin(),reach.end());
	this->reach_minus_one.erase(reach_minus_one.begin(),reach_minus_one.end());
	this->positions.erase(positions.begin(),positions.end());

        for (int i=0; i < situation->size(); ++i) {
                situation->at(i)->clear_data();
	}
}

/*
 * Tell me where are located pieces of this player.
 */
QVector<char> & Player::where_are_pieces(){
	//test if positions must be calculated
	if(positions.empty()){
		//inic list
                positions.fill('_',64);

		//fill list
                QSharedPointer<Piece> piece;
                for (int i=0; i < this->situation->size(); ++i){
                        piece = this->situation->at(i);
			(this->positions)[piece->position->get_positon()] = piece->short_name();
		}

		return positions;
	}
	else{
		return positions;
	}
}

/*
 * Calculates my reach.
 */
QVector<bool>& Player::my_reach(){
	//check if reach needs to be calculated
	if(this->reach.empty()){
		//Create and init array;
                this->reach.fill(false,64);

		//Calculate reach
                for (int i=0; i < situation->size(); ++i) {
                        QVector<bool> piece_reach = this->situation->at(i)->reach();
			for (int j = 0; j < BOARD_SIZE; ++j)
				(this->reach)[j] = (this->reach)[j] || piece_reach[j];
		}

		return this->reach;
	}
	else {
		return this->reach;
	}
}

/*
 * Calculates my reach excludding one piece.
 */
QVector<bool>& Player::my_reach_minus_one(QSharedPointer<Piece> exclude){
	//check if reach needs  to be calculated
	if(this->reach_minus_one.empty()){
		//create and init array
                this->reach_minus_one.fill(false,64);

		//Calculate reach
                for (int i=0; i < situation->size(); ++i) {
                        if(this->situation->at(i) != exclude){
                                QVector<bool> piece_reach = this->situation->at(i)->reach();
				for (int j = 0; j < BOARD_SIZE; ++j)
					(this->reach_minus_one)[j] = (this->reach_minus_one)[j] || piece_reach[j];
			}
		}

		return this->reach_minus_one;
	}
	else {
		return this->reach_minus_one;
	}
}

/*
 * Calculates my moves.
 */
QVector<bool>& Player::my_moves(){
	//check if moves need to be calculated
	if(this->moves.empty()){
		//Create and init array;
                this->moves.fill(false,64);

		//Calculate reach
                for (int i=0; i < situation->size(); ++i) {
                        QVector<bool> piece_moves = this->situation->at(i)->moves();
			for (int j = 0; j < BOARD_SIZE; ++j)
				(this->moves)[j] = (this->moves)[j] || piece_moves[j];
		}

		return this->moves;
	}
	else {
		return this->moves;
	}
}

/*
 * Finds piece positioned at a given position.
 * !!!! It clears parameter from ram!!!
 */
QSharedPointer<Piece> Player::piece_at_pos(char piece_pos){
	char curr_pos = -1;
        QSharedPointer<Piece> curr_piece;
        QSharedPointer<Piece> ret;
        for (int i=0; i < this->situation->size(); ++i) {
                curr_piece = this->situation->at(i);
		curr_pos = curr_piece->position->get_positon();
		if (piece_pos == curr_pos) {
			ret = curr_piece;
		}

		if( ret != NULL )
			break;
	}

	return ret;
}

/*
 * Checks if we loast a piece.
 */
void Player::opponent_moved(char his_move){
	//check if some piece was taken and remove it
        QSharedPointer<Piece> curr_piece;
	char curr_pos = -1;
        for (int i=0; i < this->situation->size(); ++i) {
                curr_piece = this->situation->at(i);
		curr_pos = curr_piece->position->get_positon();
		if (his_move == curr_pos){
			if(i == 0)
				cout << "bala" << endl;
                        this->situation->erase(this->situation->begin()+i);
			break;
		}
	}
}

/*
 * Prints all possible moves for curent player.
 */
void Player::print_moves(){
        QVector<bool> moves = this->my_moves();

	cout << "All possible moves: " << endl;
	cout << "  A B C D E F G H  " << endl;
	for (int i = 7; i >= 0; i--) {
		cout << i+1 << " ";
		for (int j = 0; j < 8; ++j) {
			if(moves[i*8+j] == true)
				cout << 'X' << ' ';
			else
				cout << '_' << ' ';
		}
		cout << i+1 << endl;
	}
	cout << "  A B C D E F G H  " << endl << endl;
}

/*
 * Returns PGN notation for given move.
 */
QString Player::get_pgn(int i){ return pgn_moves.at(i); }

/*
 * Returns length of PGN vector.
 */
int Player::get_pgn_size(){ return this->pgn_moves.size(); }

/*
 * Get a piece identified by notation character.
 */
QSharedPointer<Piece> Player::get_piece(char name){
        QSharedPointer<Piece> ret;
        for (int i=0; i < this->situation->size(); ++i) {
                ret = this->situation->at(i);
		if(ret->short_name() == name)
			break;
                ret.clear();
	}

	return ret;
}

/*
 * Chooses move regarding random function.
 */
char Player::choose_random_move(int * points, int piece){
        QVector<char> moves = situation->at(piece)->list_moves();
	int size = moves.size();
	int sum_points = 0;
	for (int i = 0; i < size; ++i) {
		sum_points += points[i];
	}

	//choose move to take
	int point = rand() % (sum_points+1);
	int i=0;
	while(point > 0){
		point -= points[i];
		i++;
	}
	i--;

	if(i==-1)
		i=0;

	return moves[i];
}

/*
 * Makes a copy of situation for simualtion purpuses.
 */
void Player::copy_situation(){
        QSharedPointer< QVector< QSharedPointer<Piece> > > temp = this->situation_copy;
        this->situation_copy = this->situation;		//save current situation
        this->situation = temp;


	//duplicate piece info
        QSharedPointer<Piece> curr_piece, new_piece;
        for(int i=0; i<this->situation_copy->size(); i++){
                this->situation->push_back(this->situation_copy->at(i)->duplicate());
        }

	//disable pgn write
	//this->write_pgn = false;
	this->save_history = true;
	this->game_history_move.clear();
	this->game_history_piece.clear();
	this->clear_data();
}

/*
 * Restores a situation->
 */
void Player::restore_situation(){
        QSharedPointer< QVector< QSharedPointer<Piece> > > temp = this->situation_copy;
        this->situation_copy = this->situation;		//save current situation
        this->situation = temp;

        this->situation_copy->clear();

	//enable pgn write
	//this->write_pgn = true;
	this->save_history = false;
//	this->game_history_move.clear();
//	this->game_history_piece.clear();
	this->clear_data();
}

/*
 * Duplicates player in a form defined by a parameter.
 * @param type a type of player to return
 */
QSharedPointer<Player> Player::duplicate(int type){
        QSharedPointer< QVector< QSharedPointer<Piece> > > new_situation(new QVector< QSharedPointer<Piece> >());
        for(int i=0; i<this->situation->size(); i++){
                QSharedPointer<Piece> test = this->situation->at(i)->duplicate();
                new_situation->push_back(test);
        }

        QSharedPointer<Player> ret;
        if(type == Player::RANDOM_PLAYER){
                QSharedPointer<Player> rand(new RandomPlayer(new_situation));
                return rand;
        }
        else if (type == Player::MCTS_PLAYER){
                QSharedPointer<Player> win(new MCTSPlayer(new_situation));
                return win;
        }
        else if (type == Player::APPROACH_KING_PLAYER){
                QSharedPointer<Player> win(new ApproachKingPlayer(new_situation));
                return win;
        }
        else if ( type == Player::KBNK_LOOSER_PLAYER){
                QSharedPointer<Player> loose(new KBNKLooserPlayer(new_situation));
                return loose;
	}
        else if ( type == Player::TO_CENTER_PLAYER){
                QSharedPointer<Player> loose(new ToCenterPlayer(new_situation));
                return loose;
        }
        else{
            qDebug() << "[Player::duplicate()] Player type" << type << "unknown. Aborting....";
            exit(0);
        }

	return ret;
}

/*
 * Returns reference to moves history.
 */
QList<char> & Player::move_history(){ return this->game_history_move; }

/*
 * Returns reference to piece history.
 */
QList<int> & Player::piece_history(){ return this->game_history_piece; }

/**
  * Creates player from FEN string.
  *
  * @param fen FEN string
  * @param white true if building white player, false if black
  *
  * @return pointer to player
  */
QSharedPointer<Player> Player::get_player_from_FEN(QString fen, bool white, int p_type){
    //split fen to be more readeable
    QStringList list = fen.split(' ', QString::SkipEmptyParts);
    fen = list.at(0);
    QStringList pos = fen.split('/', QString::SkipEmptyParts);

    //vector of pieces
    QSharedPointer< QVector< QSharedPointer< Piece > > > pieces_sit( new QVector< QSharedPointer< Piece > >() );

    //get pos
    for(int row=0; row < pos.size(); row++){
        QString code = pos[row];
        //check if row is empty
        if(code[0] != '8'){
            //find pieces in this row
            int col = 0;
            for(int i=0; i<code.length(); i++){
                if(code[i].isNumber()){
                    col += code[i].digitValue();
                }
                else{
                    if(white && code[i].isUpper()){
                        if(code[i] == 'K')
                            pieces_sit->push_front(Player::create_piece(code[i], col, 7-row));
                        else
                            pieces_sit->push_back(Player::create_piece(code[i], col, 7-row));
                    }
                    else if(!white && code[i].isLower()){
                        if(code[i] == 'k')
                            pieces_sit->push_front(Player::create_piece(code[i], col, 7-row));
                        else
                            pieces_sit->push_back(Player::create_piece(code[i], col, 7-row));
                    }
                    col++;
                }
            }
        }
    }

    return Player::create_player(p_type,pieces_sit);
}

/**
  * Creates and returns piece from char and pos.
  *
  * @param code char code of piece
  * @param x position column
  * @param y position row
  */
QSharedPointer<Piece> Player::create_piece(QChar code, int x, int y){
    bool white = code.isUpper();
    code = code.toUpper();
    QSharedPointer<Piece> ret;
    if(code == 'K'){
        QSharedPointer<Position> pos(new Position(x,y));
        QSharedPointer<Piece> piece(new King(pos, white));
        ret = piece;
    }
    else if(code == 'Q'){
        QSharedPointer<Position> pos(new Position(x,y));
        QSharedPointer<Piece> piece(new Queen(pos, white));
        ret = piece;
    }
    else if(code == 'R'){
        QSharedPointer<Position> pos(new Position(x,y));
        QSharedPointer<Piece> piece(new Rook(pos, white));
        ret = piece;
    }
    else if(code == 'B'){
        QSharedPointer<Position> pos(new Position(x,y));
        QSharedPointer<Piece> piece(new Bishop(pos, white));
        ret = piece;
    }
    else if(code == 'N'){
        QSharedPointer<Position> pos(new Position(x,y));
        QSharedPointer<Piece> piece(new Knight(pos, white));
        ret = piece;
    }
//TODO pesant is not implemented
//    else if(code == 'P'){
//        QSharedPointer<Position> pos(new Position(x,y));
//        QSharedPointer<Piece> piece(new Pesant(pos, white));
//        ret = piece;
//    }

    return ret;
}

/**
  * Creates player.
  *
  * @param type player type
  * @param s player's situation
  *
  * @return player
  */
QSharedPointer<Player> Player::create_player(int type, QSharedPointer< QVector< QSharedPointer< Piece > > > s){
    QSharedPointer<Player> ret;
    //Random Player
    if(type == 0){
        QSharedPointer<Player> p(new RandomPlayer(s));
        ret = p;
    }
    //MCTS Player
    else if(type == 1){
        QSharedPointer<Player> p(new MCTSPlayer(s));
        ret = p;
    }
    //Table Base
    else if(type == 2){
        qDebug() << "[Player::create_player()] Table balse not implemented!";
        exit(1);
//        QSharedPointer<Player> p(new TableBlackPlayer(s));
//        ret = p;
    }
    //To center heuristics
    else if(type == 3){
        QSharedPointer<Player> p(new ToCenterPlayer(s));
        ret = p;
    }

    return ret;
}
