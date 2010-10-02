#ifndef CONFIGPARSE_H
#define CONFIGPARSE_H

#include "config/config.h"
#include <QSharedPointer>
#include <QtCore>

class ConfigParse : public QObject{
    Q_OBJECT
private:
    QSharedPointer<Config> config;
    void loadBasic();

public:
    ConfigParse(QString, char ** );
    QString getString(QString);
    double C;
    int len;
    int N;
    int time;
    int w_type;
    int b_type;
    int mcts_b;
    int mcts_w;
    int mcts_sim_limit;
    bool output_tree;
    QString pgn;
};


#endif // CONFIGPARSE_H
