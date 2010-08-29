/*
 * TableBase.h
 *
 *  Created on: 29.5.2010
 *      Author: slashrsm
 */

#ifndef TABLEBASE_H_
#define TABLEBASE_H_

#define TABLE_SIZE 4194303

#include <vector>
#include <string>
#include "Piece.h"

class TableBase : public QObject {
    Q_OBJECT
        QString fname;
	unsigned char table_base[TABLE_SIZE];
	unsigned char positions[4];	//K B N k
	unsigned char new_positions[4];
	bool white;
        void get_positions(QSharedPointer< QVector< QSharedPointer<Piece> > > &, QSharedPointer< QVector< QSharedPointer<Piece> > > &);
	void check_mirrors();
	void mirror_situation(char, bool);
	void copy_positions();
        char get_piece_index(char, QSharedPointer< QVector< QSharedPointer<Piece> > > &);
	char convert_position(char);

public:
        TableBase(QString, bool);
	virtual ~TableBase();
	void read_table();
        QVector<char> best_move(QSharedPointer< QVector< QSharedPointer<Piece> > > &,QSharedPointer< QVector< QSharedPointer<Piece> > > &);
};

#endif /* TABLEBASE_H_ */
