#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QKeyEvent>

#include "player_plane.h"
#include "score.h"
#include "health.h"
#include "playername.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    player_plane *playerPlane ;
    Score *score ;
    Health *health ;
    playername *playerNameObj ;
    QString playerNameString ;
    static int count ;

signals:
    void startGameSignal() ;

private:
    QGraphicsView *mainView ;
    QGraphicsScene *mainScene ;
    QVBoxLayout *mainLayout ;
    QTimer *timerSpawn ;
    QMediaPlayer *gameBgMusicPlayer ;
    QMediaPlaylist *soundList ;


public slots:
    void spawnEnemies() ;
    void startGame() ;
    void stopGame() ;
};
#endif // WIDGET_H
