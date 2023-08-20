#include <QFont>
#include <QGraphicsScene>

#include "health.h"

Health::Health()
{
    this->health = 3 ;
    this->setPlainText("HEALTH : " + QString::number(this->health)) ;
    this->setFont(QFont("times",18));
    this->setDefaultTextColor(Qt::green) ;
}

int Health::decreaseHealth()
{
    health-- ;
    this->setPlainText("HEALTH : " + QString::number(this->health)) ;

    if(health == 0) {
        emit gameOverSignal() ;
        return 1 ;
    }

    return 0 ;
}
