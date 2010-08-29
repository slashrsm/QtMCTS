/*
 * TableBase.cpp
 *
 *  Created on: 29.5.2010
 *      Author: slashrsm
 */

#include "TableBase.h"
#include <vector>
#include "Piece.h"
#include "Position.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>


#define TABLE_SIZE 4194303

TableBase::TableBase(QString f, bool w) {
        this->fname = f;
        this->white = w;
        this->read_table();
}

TableBase::~TableBase() {}

/*
 * Reads KBNK table base from file.
 */
void TableBase::read_table(){
        QFile f(this->fname);
        f.open(QIODevice::ReadOnly);
        QTextStream tbase(&f);

        int i=0;
        QString value;
        while(!f.atEnd()){
                value = tbase.readLine();
                this->table_base[i] = (unsigned char) value.toUInt();
                i++;
        }

        f.close();
}

/*
 * Returns best move for this player.
 *
 * @param my vector of my Pieces
 * @param his vector of his Pieces
 *
 * @return vector of two values, where first represents piece and second move
 */
QVector<char> TableBase::best_move(QSharedPointer< QVector< QSharedPointer<Piece> > > & my, QSharedPointer< QVector< QSharedPointer<Piece> > > & his){
        this->get_positions(my,his);	//read positions index

        if (this->white){
                QVector<char> moves = my->at(0)->list_moves();
                char piece = 0;
                int index_in_positions = this->get_piece_index(0,my);
                this->copy_positions();
                this->new_positions[index_in_positions] = convert_position(moves.at(0));
                this->check_mirrors();
                unsigned int index = ((int)this->new_positions[0] * 262144) + ((int)this->new_positions[1] * 4096) + ((int)this->new_positions[2] * 64) + ((int)this->new_positions[3]);
                unsigned char dtm = this->table_base[index];
                char move = moves.at(0);


                for(int j=0; j<my->size(); j++){
                        moves = my->at(j)->list_moves();
                        index_in_positions = this->get_piece_index(j,my);

                        for(int i=0; i<moves.size(); i++){
                                this->copy_positions();
                                this->new_positions[index_in_positions] = convert_position(moves.at(i));
                                this->check_mirrors();
                                index = ((int)this->new_positions[0] * 262144) + ((int)this->new_positions[1] * 4096) + ((int)this->new_positions[2] * 64) + ((int)this->new_positions[3]);

//				cout << index <<  "\t" << (int)j << "-" << (int)moves.at(i) << ": " << (int)this->table_base[index] << endl;
                                if (dtm > 100 || (this->table_base[index] < 100 && this->table_base[index] <= dtm)){
                                        dtm = this->table_base[index];
                                        move = moves.at(i);
                                        piece = j;
//					cout << (int)j << "-" << (int)move << ": " << (int)dtm << endl;
                                }
                        }
                }

//		cout << my->at(piece)->short_name() << "-"  <<  (int)move << "White:" << (int) dtm << endl;

                QVector<char> ret;
                ret.push_back(piece);
                ret.push_back(move);
                return ret;
        }
        else {
                QVector<char> moves = my->at(0)->list_moves();
//		char piece = 0;
                this->copy_positions();
                this->new_positions[3] = convert_position(moves.at(0));
                this->check_mirrors();
                unsigned int index = ((int)this->new_positions[0] * 262144) + ((int)this->new_positions[1] * 4096) + ((int)this->new_positions[2] * 64) + ((int)this->new_positions[3]);
                unsigned char dtm = this->table_base[index];
                char move = moves.at(0);

                //DEBUG aoutput
                qDebug() << (int)moves.at(0) << "(" << (int)convert_position(moves.at(0)) << "): dtm-" << (int)this->table_base[index];

                for(int i=1; i<moves.size(); i++){
                        this->copy_positions();
                        this->new_positions[3] = convert_position(moves.at(i));
                        this->check_mirrors();
                        index = ((int)this->new_positions[0] * 262144) + ((int)this->new_positions[1] * 4096) + ((int)this->new_positions[2] * 64) + ((int)this->new_positions[3]);

                        //DEBUG aoutput
                        qDebug() << (int)moves.at(i) << "(" << (int)convert_position(moves.at(i)) << "): dtm-" << (int)this->table_base[index];

                        if (this->table_base[index] == 101){
                                dtm = this->table_base[index];
                                move = moves.at(i);
                                QVector<char> ret;
                                ret.push_back(0);
                                ret.push_back(move);
                                return ret;
                        }
                        else if (this->table_base[index] < 254 && this->table_base[index] > dtm){
                                dtm = this->table_base[index];
                                move = moves.at(i);
                        }
                }

                QVector<char> ret;
                ret.push_back(0);
                ret.push_back(move);
                return ret;
        }
}

/**
 * Reads positions indexes from situations in vectors, and saves it to
 * member array "positions" in a form [K, B, N, k].
 *
 * @param my vector of my Pieces
 * @param his vector of his Pieces
 */
void TableBase::get_positions(QSharedPointer< QVector< QSharedPointer<Piece> > > & my, QSharedPointer< QVector< QSharedPointer<Piece> > > & his){
        //get positions
        QSharedPointer< QVector< QSharedPointer<Piece> > > white = this->white ? my : his;
        QSharedPointer< QVector< QSharedPointer<Piece> > > black = this->white ? his : my;

        //DEBUG OUTPUT
        qDebug() << white->at(0)->short_name() << white->at(0)->position->get_notation() << "(" << (int)white->at(0)->position->get_tablebase_position() << ") "
                << white->at(1)->short_name() << white->at(1)->position->get_notation() << "(" << (int)white->at(1)->position->get_tablebase_position() << ") "
                << white->at(2)->short_name() << white->at(2)->position->get_notation() << "(" << (int)white->at(2)->position->get_tablebase_position() << ") "
                << black->at(0)->short_name() << black->at(0)->position->get_notation() << "(" << (int)black->at(0)->position->get_tablebase_position() << ") ";
        //DEBUG

        //get positions of pieces
        QSharedPointer<Piece> curr;
        for (int i=0; i < white->size(); i++){
                curr = white->at(i);
                if (curr->short_name() == 'K')
                        this->positions[0] = curr->position->get_tablebase_position();
                else if (curr->short_name() == 'B')
                        this->positions[1] = curr->position->get_tablebase_position();
                else if (curr->short_name() == 'N')
                        this->positions[2] = curr->position->get_tablebase_position();
        }
        this->positions[3] = black->at(0)->position->get_tablebase_position();
}

/**
 * Check if situation must be mirrored because of white king.
 * To save space we store tablebase just for white king in square a0-d4 (all other situations can be
 * transformed to this one with mirroring over lines that divide chessboard to quarters).
 */
void TableBase::check_mirrors(){
        //check white king position
        char K_row = new_positions[0] / 8;
        char K_col = new_positions[0] % 8;

        if(K_row > 3){
                for(int i=3; i>-1; i--)
                        this->mirror_situation(i,true);
        }
        else if(K_col > 3){
                for(int i=3; i>-1; i--)
                        this->mirror_situation(i,false);
        }

        this->new_positions[0] = (this->new_positions[0] / 8) * 4 + this->new_positions[0] % 4;
}

/**
 * Mirrors position at index "piece" in member array "positions".
 * If "horizontal" true, then mirrors over horizontal line, otherwse over vertical.
 *
 * @param piece index in member array "positions"
 * @param horizontal if true mirror over horizontal line, otherwise over vertical
 */
void TableBase::mirror_situation(char piece, bool horizontal){
        //int div = piece == 0 ? 4 : 8;
        int div = 8;

        if (horizontal){
                this->new_positions[(int)piece] = (7-(this->new_positions[(int)piece] / 8)) * div + this->new_positions[(int)piece] % 8;
        }
        else {
                this->new_positions[(int)piece] = (this->new_positions[(int)piece] / 8) * div + (7-(this->new_positions[(int)piece] % 8));
        }
}

/**
 * Just copies values from positions to new_positions.
 */
void TableBase::copy_positions(){
        this->new_positions[0] = this->positions[0];
        this->new_positions[1] = this->positions[1];
        this->new_positions[2] = this->positions[2];
        this->new_positions[3] = this->positions[3];
}

/*
 * Returns index of piece in member array positions.
 *
 * @param p index of piece in vector
 * @param my vector of pieces
 *
 * @return index in member array positions
 */
char TableBase::get_piece_index(char p, QSharedPointer< QVector< QSharedPointer<Piece> > > & my){
        switch(my->at(p)->short_name()){
        case 'K':
                return 0;
                break;
        case 'B':
                return 1;
                break;
        case 'M':
                return 2;
                break;

        }

        return -1;
}

/*
 * Returns position for table base, where countig begins
 * from h1, not a1.
 *
 * @param pos position index as is used algorithm (a1 = 0, h8 = 63)
 *
 * @return position as is used in table base (h1 = 0, a8 = 63)
 */
char TableBase::convert_position(char pos){
        char row = pos / 8;
        char col = pos % 8;

        return 8*row + (7-col);
}
