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
#include "RandomPlayer.h"
#include "KBNKLooserPlayer.h"
#include "KBNKWinnerPlayer.h"

/*
 * Static members.
 */
int Player::RANDOM_PLAYER = 0;
int Player::KBNK_WINNER_PLAYER = 1;
int Player::KBNK_LOOSER_PLAYER = 2;

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
        if(type == 0){ // Player::RANDOM_PLAYER:
                QSharedPointer<Player> rand(new RandomPlayer(new_situation));
                return rand;
        }
        else if (type == 1){ //Player::KBNK_WINNER_PLAYER:
                QSharedPointer<Player> win(new KBNKWinnerPlayer(new_situation));
                return win;
        }
        else if ( type == 2){ //Player::KBNK_LOOSER_PLAYER:
                QSharedPointer<Player> loose(new KBNKLooserPlayer(new_situation));
                return loose;
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
