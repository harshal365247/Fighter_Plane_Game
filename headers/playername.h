#ifndef PLAYERNAME_H
#define PLAYERNAME_H

#include <QGraphicsTextItem>

class playername : public QGraphicsTextItem
{
public:
    playername(QString &a_name);
    QString getPlayerName() ;
private:
    QString m_name ;
};

#endif // PLAYERNAME_H
