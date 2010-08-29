/*
 * MCTSNode.h
 *
 *  Created on: 5.9.2009
 *      Author: slashrsm
 */

#ifndef MCTSNODE_H_
#define MCTSNODE_H_

using namespace std;

#include "Player.h"
#include "MCTSPlayer.h"

#include <vector>
#include <iostream>
#include <fstream>


class MCTSNode : public QObject {
    Q_OBJECT
private:
        QVector< QSharedPointer< MCTSNode > > children;
        MCTSNode* parent;

        //WARNING: Sholud be weak reference?
        QSharedPointer<Player> my_player;
        QSharedPointer<Player> his_player;
        QSharedPointer<Player> curr_player;
        QSharedPointer<Player> curr_holder;

	int depth_limit;
//	char * move_notation;
	char piece_short_name;

	int game_type;
	bool my_turn;
	float quality();
	void decrease_depth();
	char simulate();
        void expanse(char, QList<char> &, QList<int> &, int);
	float UCT();
	int get_move(char,char);
	void register_move(char, char);

public:
	static int SELECT_TRESSHOLD;
	static float UCT_C_CONSTANT;
	static int GO_TO_BORDER_MOVES_LIMIT;
	static int GO_TO_CORNER_MOVES_LIMIT;
	static int GO_TO_CHECKMATE_MOVES_LIMIT;
	static int TIMELIMIT;
	static long NODE_COUNT;
	static int MAX_DEPTH;
	static long SIMULATION_COUNT;
	static long CREATED_NODES;
	static long DELETED_NODES;
        static long REACHED_CORNER_SIMS;
    static long ENTERED_EXPANSION;
    static int NODE_CREATION_FREQ;
    static int NODE_CREATION_COUNT;

        MCTSNode(QSharedPointer<Player>, QSharedPointer<Player>, bool, int, MCTSNode *, char, char, int, int);
	virtual ~MCTSNode();
	char select();
	void copy_situation();
	void restore_situation();
        QSharedPointer<MCTSNode> best_move();
        QSharedPointer<MCTSNode> oponent_moved(char, char);
        void export_graph(QTextStream &, int);
        void node_title(QTextStream &);
	int create_new_node(int, char, char);
	void add_visit();
	char piece_moved;
	char move;
	int visits;
	int wins;
	int depth;
};

#endif /* MCTSNODE_H_ */
