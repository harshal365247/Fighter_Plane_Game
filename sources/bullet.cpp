#include <QDebug>
#include <QList>

#include "bullet.h"
#include "enemy.h"

bullet::bullet()
{
    this->setPixmap(QPixmap(":/img/Resources/img/bullet.png").scaled(QSize(30, 60))) ;
    this->setTransformOriginPoint(this->boundingRect().center()) ;
    this->setRotation(180) ;

    timer = new QTimer(this) ;
    timer->setInterval(50) ;
    connect(timer, &QTimer::timeout, this, &bullet::move) ;
}

void bullet::move()
{
    QList<QGraphicsItem*> collidingItems = this->collidingItems() ;

    foreach(QGraphicsItem *item, collidingItems){
        if(typeid(*item) == typeid(Enemy)){
            containerWidgetObj->widgetObj->score->increaseScore() ;
            emit destroySoundSignal() ;
            this->scene()->removeItem(item) ;
            this->scene()->removeItem(this) ;
            delete this ;
            delete item ;
            return ;
        }
    }

    this->setPos(this->x(), this->y()-15) ;

    if(this->y() < 0 - this->pixmap().height()){
        this->scene()->removeItem(this) ;
        delete this ;
    }
}
