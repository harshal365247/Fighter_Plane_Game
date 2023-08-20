#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>


#include "containerwidget.h"

extern containerWidget *containerWidgetObj ;

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy();
    ~Enemy() ;

private:
    QTimer *timer ;
private slots:
    void move() ;
};

#endif // ENEMY_H
