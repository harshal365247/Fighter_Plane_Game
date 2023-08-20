#include <QApplication>
#include <QScreen>

#include "player_plane.h"
#include "bullet.h"

player_plane::player_plane()
{
    bulletPlayList = new QMediaPlaylist(this) ;
    bulletPlayList->addMedia(QUrl("qrc:/sound/Resources/sound/bulletSound.mp3")) ;
    bulletPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce) ;

    bulletSoundPlayer = new QMediaPlayer(this) ;
    bulletSoundPlayer->setPlaylist(bulletPlayList) ;

    destroyPlaylist = new QMediaPlaylist(this) ;
    destroyPlaylist->addMedia(QUrl("qrc:/sound/Resources/sound/explosion.mp3")) ;
    destroyPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce) ;

    destroyPlayer = new QMediaPlayer(this) ;
    destroyPlayer->setPlaylist(destroyPlaylist) ;

    enableFiringTimer = new QTimer(this) ;
    enableFiringTimer->setTimerType(Qt::PreciseTimer) ;
    enableFiringTimer->start(200) ;

    connect(enableFiringTimer, &QTimer::timeout, this, &player_plane::enableFiringSlot) ;

    QScreen *screen = QApplication::primaryScreen() ;
    QRect geometry = screen->availableGeometry() ;
    int width = geometry.width() ;
    int height = geometry.height() ;

    this->setPixmap(QPixmap(":/img/Resources/img/player.png").scaled(QSize((int)(width/6),(int)(height/3)))) ;
}

void player_plane::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Left:
        if( (this->x()  + this->pixmap().width() / 2 ) >= this->scene()->sceneRect().left() ){
            this->setPos(this->x()-20, this->y()) ;
            break;
        }
        break;
    case Qt::Key_Right:
        if( ( this->x() + this->pixmap().width() / 2 ) < this->scene()->sceneRect().right() ){
            this->setPos(this->x()+20, this->y()) ;
            break;
        }
        break;
    case Qt::Key_Up:
        if(this->y() >= this->scene()->sceneRect().top() + this->pixmap().height() ){
            this->setPos(this->x(), this->y()-10) ;
            break;
        }
        break;
    case Qt::Key_Down:
        if(this->y() <= this->scene()->sceneRect().bottom() - this->pixmap().height() ){
            this->setPos(this->x(), this->y()+10) ;
            break;
        }
        break;
    }
}

void player_plane::keyReleaseEvent(QKeyEvent *event)
{
    if(!firing)
        return ;
    if(event->key() == Qt::Key_Space){
        bullet *bulletObj = new bullet() ;
        connect(bulletObj, &bullet::destroySoundSignal, this, &player_plane::destroySlot) ;

        if(bulletSoundPlayer->state() == QMediaPlayer::PlayingState){
            bulletSoundPlayer->setPosition(0) ;
        }
        bulletSoundPlayer->play() ;

        bulletObj->setPos(this->x() + this->pixmap().width()/2, this->y()-2) ;
        this->scene()->addItem(bulletObj) ;
        bulletObj->timer->start() ;
        firing = false ;
    }
}

void player_plane::destroySlot()
{
    if(destroyPlayer->state() == QMediaPlayer::PlayingState){
        destroyPlayer->setPosition(0) ;
    }
    destroyPlayer->play() ;
}

void player_plane::enableFiringSlot()
{
    firing = true ;
}
