#include "ConfigParse.h"
#include <QString>
#include <QFile>
#include <QSharedPointer>
#include <QtCore>
#include <string>

/**
  * Config file parser. Gets config filename and table of env
  * variables and loads Config object, which builds map of
  * pairs <key> = <value> from config file.
  *
  * Aborts if file was not found.
  *
  * More about Config object: http://www.codeproject.com/KB/files/config-file-parser.aspx
  */
ConfigParse::ConfigParse(QString filename, char ** envp){
    QFile fname(filename);
    if(fname.exists()){
        qDebug() << "[ConfigParse] Loading config from " << filename;
        QSharedPointer<Config> temp_p(new Config(filename.toStdString(), envp));
        this->config = temp_p;
        this->loadBasic();
    }
    else{
        qDebug() << "[ConfigParse] Config file " << filename << "not found!";
        qDebug() << "[ConfigParse] Aborting...";
        exit(1);
    }
}

/**
  * Gets value from config file.
  *
  * @param key name of setting to be returned
  * @return string representation of value from config file
  */
QString ConfigParse::getString(QString key){
    map<string, string> syms = this->config->getSymbols();
    string val = syms[key.toStdString()];
    return QString(val.c_str());
}

/**
  * Loads basic settings from config file.
  * As C, N, length, time, ...
  *
  */
void ConfigParse::loadBasic(){
    QString s_C(this->config->pString("C").c_str());
    this->C = s_C.toDouble();
    this->N = this->config->pInt("N");
    this->len = this->config->pInt("len");
    this->time = this->config->pInt("time");
    this->pgn = QString(this->config->pString("pgn_name").c_str());
    this->w_type = this->config->pInt("white_type");
    this->b_type = this->config->pInt("black_type");
    this->mcts_b = this->config->pInt("mcts_b");
    this->mcts_w = this->config->pInt("mcts_w");
    this->mcts_sim_limit = this->config->pInt("mcts_sim_limit");
    this->output_tree = this->config->pBool("output_tree");
}
