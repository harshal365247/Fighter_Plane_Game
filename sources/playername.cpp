#include <QFont>

#include "playername.h"

playername::playername(QString &a_name)
{
    this->m_name = a_name ;
    this->setPlainText("PLAYER : " + this->m_name) ;
    this->setFont(QFont("times",18)) ;
    this->setDefaultTextColor(Qt::white) ;
}

QString playername::getPlayerName()
{
    return this->m_name ;
}
