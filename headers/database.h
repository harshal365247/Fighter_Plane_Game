#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class database : public QObject
{
    Q_OBJECT
public:
    explicit database(QObject *parent = nullptr);
    ~database() ;

    QSqlDatabase local_db ;
    QString db_path ;

public slots:
    void prepareTable() ;
    void InsertScore(QString playerName, int score) ;
    void getScoreList(QList<int> &scoreList, QList<QString> &nameList) ;

signals:

};

#endif // DATABASE_H
