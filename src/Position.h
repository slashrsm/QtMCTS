/*
 * Position.h
 *
 * Class that stores coordinates of a given piece on chessboard.
 *
 *  Created on: 1.8.2009
 *      Author: Janez Urevc [63040171]
 */

#ifndef POSITION_H_
#define POSITION_H_

using namespace std;

#include <string>
#include <map>
#include <QtCore>

/*
 * Holds data about position of a piece.
 *
 * Code is unique for each square on chessboard:
 *  - A1 = 1
 *  - B1 = 2
 *  - C1 = 3
 *  - ...
 *  - H1 = 8
 *  - A2 = 9
 *  - ....
 *  - H8 = 64
 */
class Position : public QObject {
    Q_OBJECT
private:
	char a, b, code;

public:
	Position(char, char);
	Position(char);
	virtual ~Position();
	bool set_position(char, char);
	bool set_position(char);
	char get_positon();
        QVector<char> get_coords();
        QString get_notation();
	bool same_pos(char, char);
	static char coord_to_char[8];
    static char color_map[64];
	static map<char, char> char_to_coord;
	bool same_falling_diagonal(char);
	bool same_raising_diagonal(char);
    char get_color();
    char get_tablebase_position();
};


#endif /* POSITION_H_ */
