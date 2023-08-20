#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QMediaPlaylist>


#include "containerwidget.h"

extern containerWidget *containerWidgetObj ;

class bullet : public  QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet();
    QTimer *timer ;

private:

public slots:
    void move() ;

signals:
    void destroySoundSignal() ;

};

#endif // BULLET_H
