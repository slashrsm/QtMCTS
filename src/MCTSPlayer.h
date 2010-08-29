/*
 * MCTSPlayer.h
 *
 *  Created on: 5.9.2009
 *      Author: slashrsm
 */

#ifndef MCTSPLAYER_H_
#define MCTSPLAYER_H_

using namespace std;

#include "Player.h"
#include "MCTSNode.h"

#include <string>
#include <fstream>

class MCTSNode;

class MCTSPlayer: public Player {
    Q_OBJECT
private:
        QSharedPointer<MCTSNode> tree;
	int game_state;

public:
        MCTSPlayer(QSharedPointer< QVector< QSharedPointer<Piece> > >);
	virtual ~MCTSPlayer();
	char move(int);
	void opponent_moved(char);
        virtual void set_oponent(QSharedPointer<Player>);
        void export_graph(QString, int);
	void check_simulation_game();
	bool is_at_border();
	bool is_in_corner();
	bool is_in_corner_area();
};

#endif /* MCTSPLAYER_H_ */
