/*
 * Position.cpp
 *
 *  Created on: 1.8.2009
 *      Author: slashrsm
 */

using namespace std;

#include <map>
#include <string>
#include "Position.h"

/*
 * Constructors.
 */
Position::Position(char x, char y) {
	this->set_position(x,y);
}

Position::Position(char code) {
	this->set_position(code);
}

/*
 * Destrcutor.
 */
Position::~Position() {
	// TODO Auto-generated destructor stub
}

/*
 * Sets position coordinates.
 */
bool Position::set_position(char x, char y){
	if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
		this->a = x;
		this->b = y;
		this->code = y*8 + x;
		return true;
	}
	else
		return false;
}

/*
 * Sets position code.
 */
bool Position::set_position(char code){
	if(code >= 0 && code <= 63){
		this->code = code;
		this->a = code % 8;
		this->b = code / 8;
		return true;
	}
	else{
		return false;
	}

}

/*
 * Returns position coordinates.
 */
QVector<char> Position::get_coords(){
        QVector<char> curr_pos;
        curr_pos.push_back(this->a);
        curr_pos.push_back(this->b);
	return curr_pos;
}

/*
 * Returns position code.
 */
char Position::get_positon(){
	return this->code;
}

/*
 * Returns chess notation for this position.
 */
QString Position::get_notation(){
        char c = Position::coord_to_char[(int)(this->a)];
        QString ret(c);
        ret += ('1'+this->b);
	return ret;
}

/*
 * Checks if given position is same to this.
 */
bool Position::same_pos(char a, char b){
	return a == this->a && b == this->b;
}

/*
 * Returns falling diagonal.
 */
bool Position::same_falling_diagonal(char pos){
	char x = pos % 8;
	char y = pos / 8;

	return (a-x) == -(b-y);
}

/*
 * Returns raising diagonal.
 */
bool Position::same_raising_diagonal(char pos){
	char x = pos % 8;
	char y = pos / 8;

	return (a-x) == (b-y);
}

/*
 * Returns color of current position.
 * return char color 'W' or 'B'
 */
char Position::get_color(){
    return Position::color_map[(int)this->code];
}

/*
 * Returns position for table base, where countig begins
 * from h1, not a1.
 */
char Position::get_tablebase_position(){
	return b * 8 + (7 - a);
}

char Position::coord_to_char[8];
char Position::color_map[64];
map<char, char> Position::char_to_coord;

