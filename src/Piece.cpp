/*
 * Piece.cpp
 *
 *  Created on: 1.8.2009
 *      Author: slashrsm
 */

using namespace std;

#include <iostream>
#include <cstdlib>
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"

#define BOARD_SIZE 64

Piece::Piece(QSharedPointer<Position> pos, bool w) {
	position = pos;
	white = w;
}

Piece::~Piece() {}

/*
 * Checks if move is valid.
 */
//bool Piece::is_valid(char p){ return true; }

/*
 * Returns short name of this piece.
 */
char Piece::short_name(){ return 'U'; }

/*
 * Make a move.
 */
bool Piece::move(char p){
        position->set_position(p);

//	delete[] this->saved_moves;
//	this->saved_moves = NULL;
//	delete[] this->saved_reach;
//	this->saved_reach = NULL;
//	delete this->saved_list_moves;
//	this->saved_list_moves = NULL;
	return true;
}

/*
 * Clears local saved data.
 */
void Piece::clear_data(){
	this->saved_moves.erase(saved_moves.begin(), saved_moves.end());
	this->saved_list_moves.erase(saved_list_moves.begin(), saved_list_moves.end());
	this->saved_reach.erase(saved_reach.begin(), saved_reach.end());
}

/*
 * Get reach for this piece.
 */
QVector<bool> & Piece::reach(){ return this->saved_reach; }

/*
 * Get valid moves list for this piece.
 */
QVector<bool> & Piece::moves(){ return this->saved_moves; }

/*
 * Make a list of moves.
 */
QVector<char> & Piece::list_moves(){
	if(this->saved_list_moves.empty()){
                QVector<bool> moves = this->moves();
		for (char i = 0; i < BOARD_SIZE; ++i)
			if (moves[i])
				this->saved_list_moves.push_back(i);

		return this->saved_list_moves;
	}
	else {
		return this->saved_list_moves;
	}
}


/*
 * Calculate manhattan distance from this piece to a given position.
 */
//TODO test!!!
char Piece::mdistance_to_pos(char his){
	char mine = this->position->get_positon();
	return abs(mine%8 - his%8) + abs(mine/8 - his/8);
}

/*
 * Calculate manhattan distance from this piece to an other piece.
 */
//TODO test!!
char Piece::mdistance_to_piece(QSharedPointer<Piece> p){
	return this->mdistance_to_pos(p->position->get_positon());
}

/*
 * Prints reach to std out.
 */
void Piece::print_reach(){
	cout << "--- Reach for " << this->short_name() << " ---" << endl;
	this->print_array(this->reach());
	cout << "--- End Reach ---" << endl;
}

/*
 * Prints moves to std out.
 */
void Piece::print_moves(){
	cout << "--- Moves for " << this->short_name() << " ---" << endl;
	this->print_array(this->moves());
	cout << "--- End moves ---" << endl;
}

/*
 * Prints given array to std out
 */
void Piece::print_array(QVector<bool> & array){
	cout << "  A B C D E F G H  " << endl;
	for (int i = 7; i >= 0; i--) {
		cout << i+1 << " ";
		for (int j = 0; j < 8; ++j) {
			if(array[i*8+j] == true)
				cout << 'X' << ' ';
			else
				cout << '_' << ' ';
		}
		cout << i+1 << endl;
	}
	cout << "  A B C D E F G H  " << endl << endl;
}

/*
 * Duplicates this object.
 */
QSharedPointer<Piece> Piece::duplicate(){
        QSharedPointer<Piece> new_piece;
        QSharedPointer<Position> new_position(new Position(this->position->get_positon()));
        if(this->short_name() == 'K'){
                QSharedPointer<Piece> piece(new King(new_position, this->white));
                new_piece = piece;
        }
        else if(this->short_name() == 'B'){
                QSharedPointer<Piece> piece(new Bishop(new_position, this->white));
                new_piece = piece;
        }
        else if(this->short_name() == 'N'){
                QSharedPointer<Piece> piece(new Knight(new_position, this->white));
                new_piece = piece;
        }
        else if(this->short_name() == 'Q'){
                QSharedPointer<Piece> piece(new Queen(new_position, this->white));
                new_piece = piece;
        }
        else if(this->short_name() == 'R'){
                QSharedPointer<Piece> piece(new Rook(new_position, this->white));
                new_piece = piece;
        }

	return new_piece;
}
