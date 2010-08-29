/*
 * main.cpp
 *
 *  Created on: 1.8.2009
 *      Author: slashrsm
 */

using namespace std;

#include "environment.h"
#include "Position.h"
#include "Piece.h"
#include "RandomPlayer.h"
#include "KBNKLooserPlayer.h"
#include "KBNKWinnerPlayer.h"
#include "TableBlackPlayer.h"
#include "TableWhitePlayer.h"
#include "MCTSPlayer.h"
#include "Bishop.h"    
#include "Knight.h"
#include "King.h"
#include "Game.h"
#include "GoToBorderGame.h"
#include "GoToCornerGame.h"
#include "GoToCornerDirectGame.h"

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>

void fill_mappings(){
        // Coordinates mapping
	Position::coord_to_char[0] = 'a';
	Position::coord_to_char[1] = 'b';
	Position::coord_to_char[2] = 'c';
	Position::coord_to_char[3] = 'd';
	Position::coord_to_char[4] = 'e';
	Position::coord_to_char[5] = 'f';
	Position::coord_to_char[6] = 'g';
	Position::coord_to_char[7] = 'h';

	for (int i = 0; i < BOARD_SIDE; ++i) {
		Position::char_to_coord.insert( pair<char, char>( Position::coord_to_char[i], i));
	}

        // Color mapping
        for (int i=0; i<64; i++){
            int line = (i / 8) % 2;
            int col = i % 2;

            if (line == col)
                Position::color_map[i] = 'B';
            else
                Position::color_map[i] = 'W';
        }

        // DEBUG: Print color map
//        for (int i=7; i>=0; i--){
//            for (int j=0; j<=7; j++){
//                cout << Position::color_map[i*8+j] << ' ';
//            }
//            cout << endl;
//        }

}

int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);

	if(argc == 0 || (argc > 1 && argv[1][0] == 'h')){
		cout << "Parameters to give:" << endl;
		cout << "\t1. Time limit for one move [s]" << endl;
		cout << "\t2. Limit for game length" << endl;
		cout << "\t3. N tresshold in nodes" << endl;
		cout << "\t4. Constant C in UCT expression" << endl;
		cout << "\t5. PGN filename (without .pgn)" << endl;
		cout << endl;
		cout << "Author: JAnez Urevc, janez@janezek.org" << endl;

		exit(0);
	}

	/* Read params:
	 * 	1. Time limit for one move
	 * 	2. Limit for game length
	 * 	3. N tresshold in nodes
	 * 	4. Constant C in UCT expression
	 */
	int N, L, t;
	float C;
        QString pgn_filename;

        // Read algorithm params
	t = atoi(argv[1]); 	if(t == -1) t = 1;
	L = atoi(argv[2]);	if(L == -1) L = 50;
	N = atoi(argv[3]);      if(N == -1) N = 100;
        QString c_str(argv[4]);
        C = c_str.toFloat();    if(C == -1) C = 0.7;

        // Read pgn filename
        pgn_filename = argv[5];
        pgn_filename += ".pgn";

        // Tell algorithm about params
	MCTSNode::SELECT_TRESSHOLD = N;
	MCTSNode::UCT_C_CONSTANT = C;

        // Output some data about current run to stdout.
	time_t curr_time;
	time(&curr_time);
	cout << "---===Running MCTS game - KBNK ending===---"  << endl;
	cout << "Game start: " << ctime(&curr_time);
        //cout << "Goal: " << "Reach edge" << endl;
	cout << "Single simulation time: " << t << "s" << endl;
	cout << "Game length: " << L << " moves" << endl;
	cout << "N tresshold for selection in MCTS: " << N << " visits" << endl;
	cout << "C constant in UCT formula: " << C << endl;

	// Some initial stuff (fill mappingss for ccordinates and init random seed
	fill_mappings();
	srand ( time(NULL) );

//	int i=0, big_start=clock(), big_end = 0;
//	while(i < 100){
        // white player
        QSharedPointer< QVector< QSharedPointer< Piece > > > white_s( new QVector< QSharedPointer< Piece > >() );
        QSharedPointer<Player> white( new MCTSPlayer(white_s) );
//	TableWhitePlayer * white = new TableWhitePlayer(white_s);
//	RandomPlayer * white = new RandomPlayer(white_s);

	//black player
        QSharedPointer< QVector< QSharedPointer< Piece > > > black_s( new QVector< QSharedPointer< Piece > >() );
        QSharedPointer<Player> black( new RandomPlayer(black_s) );
//	RandomPlayer * black = new RandomPlayer(black_s);
// 	KBNKLooserPlayer * black = new KBNKLooserPlayer(black_s);


	//white pieces
        QSharedPointer<Position> kpos(new Position(2,2));
        QSharedPointer<Position> npos(new Position(3,3));
        QSharedPointer<Position> bpos(new Position(2,3));
        QSharedPointer<Piece> k(new King(white, black, kpos, true));
        QSharedPointer<Piece> n(new Knight(white, black, npos, true));
        QSharedPointer<Piece> b(new Bishop(white, black, bpos, true));
        white_s->push_back(k);
        white_s->push_back(n);
        white_s->push_back(b);

	//black Pieces
        QSharedPointer<Position> bkpos(new Position(0,0));
        QSharedPointer<Piece> bk(new King(black, white, bkpos, false));
        black_s->push_back(bk);

	//game
        int start = 0, end = 0;
        GoToCornerDirectGame game(white,black,L,t,"MCTS vs. KBNK_Looser",pgn_filename,false,false);
        start = clock();
        game.play();
        end = clock();
        game.write_pgn();

        cout << "Processed in: " << ((double)(end-start))/CLOCKS_PER_SEC << endl;
//	i++;
//	}
//	big_end = clock();
//	cout << "Total: " << ((double)(big_end-big_start))/CLOCKS_PER_SEC << endl;

        return 0;
}
