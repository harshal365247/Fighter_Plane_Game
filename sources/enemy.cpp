#include <QGraphicsScene>
#include <QDebug>
#include <QApplication>
#include <QScreen>

#include "enemy.h"

Enemy::Enemy()
{
    QScreen *screen = QApplication::primaryScreen() ;
    QRect geometry = screen->availableGeometry() ;
    int width = geometry.width() ;
    int height = geometry.height() ;

    this->setPixmap(QPixmap(":/img/Resources/img/enemy.png").scaled(QSize((int)(width/6.4),(int)(height/4.5)))) ;
    this->setTransformOriginPoint(this->boundingRect().center()) ;
    this->setRotation(180) ;

    timer = new QTimer(this) ;
    timer->setInterval(50) ;
    connect(timer, &QTimer::timeout, this, &Enemy::move) ;
    timer->start() ;
}

Enemy::~Enemy()
{

}

void Enemy::move()
{

    if(this->y() > this->scene()->sceneRect().bottom() + 100){
        int deleted = containerWidgetObj->widgetObj->health->decreaseHealth() ;
        if(deleted) return ;

        this->scene()->removeItem(this) ;
        delete this ;
        return ;
    }
    this->setPos(this->x(), this->y()+10) ;
}
