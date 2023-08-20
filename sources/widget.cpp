#include <cstdlib>
#include <QShortcut>
#include <QScreen>

#include "widget.h"
#include "enemy.h"

int Widget::count ;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout() ;
    QRect rect = this->screen()->availableGeometry() ;
    this->setFixedSize(rect.width()-25, rect.height()-50) ;
    this->setWindowState(Qt::WindowMaximized) ;
    this->setAttribute(Qt::WA_TransparentForMouseEvents) ;

    mainView = new QGraphicsView() ;
    mainScene = new QGraphicsScene() ;

    timerSpawn = new QTimer(this) ;
    score = new Score() ;
    health = new Health() ;
    Widget::count = 0 ;

    mainScene->setBackgroundBrush(QBrush(":/img/Resources/img/bg.png")) ;

    connect(this, &Widget::startGameSignal, this, &Widget::startGame) ;

    mainView->setScene(mainScene) ;
    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff) ;
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff) ;

    mainLayout->addWidget(mainView) ;
    this->setLayout(mainLayout) ;
}

Widget::~Widget()
{
    delete score ;
    delete health ;

    score = nullptr ;
    health = nullptr ;
}

void Widget::spawnEnemies()
{
    if(++(Widget::count) > 10){
        timerSpawn->setInterval(timerSpawn->interval()-250) ;
        Widget::count = 0 ;
    }

    Enemy *enemy = new Enemy() ;
    int randomPos = ( (rand() % (int)( (this->mainScene->sceneRect().width()-200) - 100 + 1)) + 100 ) ;
    enemy->setPos(randomPos, 0) ;
    mainScene->addItem(enemy) ;
}

void Widget::startGame()
{
    playerPlane = new player_plane() ;
    playerPlane->setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);
    playerPlane->setFocus() ;
    mainScene->addItem(playerPlane) ;
    mainScene->setFocusItem(playerPlane) ;

    if(timerSpawn == nullptr) timerSpawn = new QTimer() ;
    if(score == nullptr) score = new Score() ;
    if(health == nullptr) health = new Health() ;

    connect(timerSpawn, &QTimer::timeout, this, &Widget::spawnEnemies) ;
    timerSpawn->start(5000) ;
    timerSpawn->setInterval(2000) ;

    score->setPos(score->x()+15, score->y()+15) ;
    mainScene->addItem(score) ;

    health->setPos(health->x()+15, score->y()+35) ;
    mainScene->addItem(health) ;

    playerNameObj = new playername(this->playerNameString) ;
    playerNameObj->setPos(playerNameObj->x() + this->width() - ( 1.5 * playerNameObj->boundingRect().width() )  , playerNameObj->y()+15) ;
    mainScene->addItem(playerNameObj) ;

    soundList = new QMediaPlaylist() ;
    soundList->addMedia(QUrl("qrc:/sound/Resources/sound/bgMusic.mp3")) ;
    soundList->setCurrentIndex(0) ;
    soundList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop) ;

    gameBgMusicPlayer = new QMediaPlayer() ;
    gameBgMusicPlayer->setPlaylist(soundList) ;
    gameBgMusicPlayer->play() ;
    gameBgMusicPlayer->setVolume(10) ;

    mainScene->setSceneRect(0, 0, this->width(), this->height()) ;  

    playerPlane->setPos(mainScene->width()/2 - playerPlane->pixmap().width()/2, mainScene->height() - playerPlane->pixmap().height() - 50) ;

}

void Widget::stopGame()
{
     timerSpawn->stop() ;
     gameBgMusicPlayer->stop() ;
     Widget::count = 0 ;

     mainScene->removeItem(playerPlane) ;
     mainScene->removeItem(health) ;
     mainScene->removeItem(score) ;
     mainScene->removeItem(playerNameObj) ;

     QList<QGraphicsItem*> itemList = this->mainScene->items() ;

     for(int i = 0; i < itemList.size(); i++){
         this->mainScene->removeItem(itemList[i]) ;
         delete itemList[i] ;
     }

     delete playerNameObj ;
     delete health ;
     delete score ;
     delete timerSpawn ;
     delete soundList ;
     delete gameBgMusicPlayer ;

     playerNameObj = nullptr ;
     health = nullptr ;
     score = nullptr ;
     timerSpawn = nullptr ;
     soundList = nullptr ;
     gameBgMusicPlayer = nullptr ;
}

