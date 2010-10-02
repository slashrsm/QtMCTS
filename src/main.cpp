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
#include "ToCenterPlayer.h"
#include "ApproachKingPlayer.h"
#include "TableBlackPlayer.h"
#include "TableWhitePlayer.h"
#include "MCTSPlayer.h"
#include "Bishop.h"    
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include "King.h"
#include "Game.h"
#include "GoToBorderGame.h"
#include "GoToCornerGame.h"
#include "GoToCornerDirectGame.h"
#include "ConfigParse.h"

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>

ConfigParse * config;

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

int main(int argc, char *argv[], char* envp[]){
    QCoreApplication app(argc, argv);

    //Short help message.
    if((argc > 1 && argv[1][0] == 'h')){
        qDebug() << "Config file name must be passed to program as argument.";
        qDebug() << "If no argument is passed program tries to load ./config.conf.";

        exit(0);
    }

    //Parse config file
    if(argc > 1){
        QString config_fname(argv[1]);
        config = new ConfigParse(config_fname, envp);
    }
    else{
        config = new ConfigParse("config.conf", envp);
    }
    MCTSNode::SELECT_TRESSHOLD = config->N;
    MCTSNode::UCT_C_CONSTANT = config->C;


    // Output some data about current run to stdout.
    time_t curr_time;
    time(&curr_time);
    qDebug() << "---===Running MCTS game - KBNK ending===---";
    qDebug() << "Game start: " << QDate::currentDate().toString() << " - " << QTime::currentTime().toString();
    qDebug() << "Single simulation time: " << config->getString("time") << "s";
    qDebug() << "Game length: " << config->getString("len") << " moves";
    qDebug() << "N tresshold for selection in MCTS: " << config->getString("N") << " visits";
    qDebug() << "C constant in UCT formula: " << config->getString("C");
    qDebug() << "White player type:" << config->w_type;
    qDebug() << "Black player type:" << config->b_type;
    qDebug() << "MCTS white player type:" << config->mcts_w;
    qDebug() << "MCTS black player type:" << config->mcts_b;
    qDebug() << "MCTS simulation limit per move:" << config->mcts_sim_limit;

    // Some initial stuff (fill mappingss for ccordinates and init random seed
    fill_mappings();
    srand ( time(NULL) );

    // create players
    QSharedPointer<Player> white;
    QSharedPointer<Player> black;
    white = Player::get_player_from_FEN(config->getString("FEN"), true, config->w_type);
    black = Player::get_player_from_FEN(config->getString("FEN"), false, config->b_type);
    Game::WHITE_START_PIECE_COUNT = white->situation->size();
    Game::BLACK_START_PIECE_COUNT = black->situation->size();
    MCTSPlayer::MCTS_WHITE_SIM_TYPE = config->mcts_w;
    MCTSPlayer::MCTS_BLACK_SIM_TYPE = config->mcts_b;
    MCTSPlayer::MCTS_SIM_LIMIT = config->mcts_sim_limit;

    // game string
    QString game_string;
    game_string += "C=";
    game_string += QString::number(config->C);
    game_string += " N=";
    game_string += QString::number(config->N);
    game_string += " t=";
    game_string += QString::number(config->time);
    game_string += " white=";
    game_string += QString::number(config->w_type);
    game_string += " black=";
    game_string += QString::number(config->b_type);

    //game
    int start = 0, end = 0;
    Game game(white,black,config->len,config->time,game_string,config->pgn,false,false);
    start = clock();
    game.play();
    end = clock();
    game.write_pgn();

    cout << "Processed in: " << ((double)(end-start))/CLOCKS_PER_SEC << endl;

    delete config;
    return 0;
}
