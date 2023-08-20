#ifndef PLAYER_PLANE_H
#define PLAYER_PLANE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QHash>

class player_plane : public QObject, public QGraphicsPixmapItem
{
public:
    player_plane();
    QMediaPlayer *destroyPlayer ;
    QMediaPlaylist *destroyPlaylist ;
    void keyPressEvent(QKeyEvent *event) ;
    void keyReleaseEvent(QKeyEvent *event) ;
    void destroySlot() ;
private:
    QMediaPlayer *bulletSoundPlayer ;
    QMediaPlaylist *bulletPlayList ;
    QTimer *enableFiringTimer ;
    int firing = false ;

private slots:
    void enableFiringSlot() ;

};

#endif // PLAYER_PLANE_H
