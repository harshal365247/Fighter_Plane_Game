#include <QStandardPaths>
#include <QVariant>
#include <QDebug>
#include <QDir>
#include <QFile>

#include "database.h"

database::database(QObject *parent)
    : QObject{parent}
{
    db_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) ;

    local_db = QSqlDatabase::addDatabase("QSQLITE") ;
    local_db.setDatabaseName(db_path) ;

    if(!local_db.open()){
        qDebug() << "cannot open DB " << local_db.lastError() ;
    }

    this->prepareTable() ;

}

database::~database()
{
    local_db.close() ;
}

void database::prepareTable()
{
    QSqlQuery query(local_db) ;
    query.prepare("CREATE TABLE IF NOT EXISTS score_table( player_name TEXT, score INT)") ;

    if(!query.exec()){
        qDebug() << "DB ERROR : " << query.lastError() ;
    }
}

void database::InsertScore(QString playerName, int score)
{
    QSqlQuery query(local_db) ;
    query.prepare("INSERT INTO score_table (player_name, score) VALUES (:name, :score) ") ;
    query.bindValue(":name", playerName) ;
    query.bindValue(":score", score) ;

    if(!query.exec()){
        qDebug() << "DB ERROR : " << query.lastError() ;
    }

    query.prepare("DELETE FROM score_table WHERE score NOT IN ( SELECT score FROM score_table ORDER BY score DESC LIMIT 10)") ;

    if(!query.exec()){
        qDebug() << "DB ERROR : " << query.lastError() ;
    }
}

void database::getScoreList(QList<int> &scoreList, QList<QString> &nameList)
{
    QSqlQuery query(local_db) ;
    query.prepare("SELECT * FROM score_table ORDER BY score DESC LIMIT 10") ;

    if(!query.exec()){
        qDebug() << "DB ERROR : " << query.lastError() ;
    }

    while(query.next()){
        QString playerName = query.value(0).toString() ;
        int score = query.value(1).toInt() ;

        scoreList.append(score) ;
        nameList.append(playerName) ;
    }
}
