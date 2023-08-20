#include <QScreen>
#include <QShortcut>

#include "gameoverwidget.h"

gameOverWidget::gameOverWidget(QWidget *parent)
    : QWidget{parent}
{
    overallLayout = new QVBoxLayout() ;
    layoutScoreLabel = new QHBoxLayout() ;
    layoutPlayerName = new QHBoxLayout() ;
    layoutForMenu = new QVBoxLayout() ;
    this->setMouseTracking(true) ;

    QRect geometry = this->screen()->availableGeometry() ;
    int height = geometry.height() ;


    buttonMusic = new QMediaPlaylist(this) ;
    buttonMusic->addMedia(QUrl("qrc:/sound/Resources/sound/buttonChange.mp3")) ;
    buttonMusic->setCurrentIndex(0) ;
    buttonMusic->setPlaybackMode(QMediaPlaylist::CurrentItemOnce) ;

    gameOverPlaylist = new QMediaPlaylist(this) ;
    gameOverPlaylist->addMedia(QUrl("qrc:/sound/Resources/sound/gameOver.mp3")) ;
    gameOverPlaylist->setCurrentIndex(0) ;
    gameOverPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce) ;

    gameOverPlayer = new QMediaPlayer(this) ;
    gameOverPlayer->setPlaylist(gameOverPlaylist) ;

    mediaPlayer = new QMediaPlayer(this) ;
    mediaPlayer->setPlaylist(buttonMusic) ;

    gameOverLabel = new QLabel() ;
    gameOverLabel->setText("GAME OVER") ;
    gameOverLabel->setAlignment(Qt::AlignCenter) ;
    gameOverLabel->setObjectName("gameOverLabel") ;

    layoutScoreLabel->addStretch() ;
    layoutScoreLabel->addWidget(gameOverLabel) ;
    layoutScoreLabel->setAlignment(Qt::AlignCenter) ;
    layoutScoreLabel->addStretch() ;

    playerNameLabel = new QLabel() ;
    playerNameLabel->setText("YOUR SCORE") ;
    playerNameLabel->setFixedSize(QSize(200, 50));
    playerNameLabel->setAlignment(Qt::AlignCenter) ;
    playerNameLabel->setObjectName("playerNameLabel") ;

    scoreLabel = new QLabel() ;
    scoreLabel->setText("0") ;
    scoreLabel->setFixedSize(QSize(200, 50)) ;
    scoreLabel->setAlignment(Qt::AlignCenter) ;
    scoreLabel->setObjectName("playerNameLabel") ;

    layoutPlayerName->setMargin( (int)(height/5.4)) ;
    layoutPlayerName->setSpacing(50) ;
    layoutPlayerName->setAlignment(Qt::AlignCenter) ;
    layoutPlayerName->addStretch() ;
    layoutPlayerName->addWidget(playerNameLabel) ;
    layoutPlayerName->addWidget(scoreLabel) ;
    layoutPlayerName->addStretch() ;

    MainMenuButton = new QPushButton() ;
    MainMenuButton->setFixedSize(QSize(300, 50)) ;
    MainMenuButton->setText("MAIN MENU") ;
    MainMenuButton->setObjectName("exitButton") ;

    buttonsList.append(MainMenuButton) ;

    QShortcut *upShortCut = new QShortcut(QKeySequence(Qt::Key_Up), this) ;
    QShortcut *downShortCut = new QShortcut(QKeySequence(Qt::Key_Down), this) ;

    layoutForMenu->addWidget(MainMenuButton) ;

    connect(downShortCut, &QShortcut::activated, this, [&](){

        QCursor::setPos(QPoint(-1,-1)) ;

        if(currentIndex < buttonsList.size() - 1){
            foreach (QPushButton* i, buttonsList) {
                i->clearFocus() ;
            }
            buttonsList[++currentIndex]->setFocus() ;
            if(mediaPlayer->state() == QMediaPlayer::PlayingState){
                mediaPlayer->setPosition(0) ;
            }
            mediaPlayer->play() ;
        }
    }) ;

    connect(upShortCut, &QShortcut::activated, this, [&](){

        QCursor::setPos(QPoint(-1,-1)) ;

        if(currentIndex == -1){
            currentIndex = buttonsList.size() ;
        }

        if(currentIndex > 0){
            foreach (QPushButton* i, buttonsList) {
                i->clearFocus() ;
            }
            buttonsList[--currentIndex]->setFocus() ;
            if(mediaPlayer->state() == QMediaPlayer::PlayingState){
                mediaPlayer->setPosition(0) ;
            }
            mediaPlayer->play() ;
        }
    }) ;

    MainMenuButton->setFocus() ;

    layoutForMenu->setAlignment(Qt::AlignCenter) ;
    layoutForMenu->setSpacing(20) ;

    overallLayout->addStretch() ;
    overallLayout->addLayout(layoutScoreLabel) ;
    overallLayout->addLayout(layoutPlayerName) ;
    overallLayout->addLayout(layoutForMenu) ;
    overallLayout->addStretch() ;
    overallLayout->setAlignment(Qt::AlignCenter) ;
    this->setLayout(overallLayout) ;
}

void gameOverWidget::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event) ;
    foreach(QPushButton* i, buttonsList){
        i->clearFocus() ;
    }
    currentIndex = -1 ;
}

void gameOverWidget::updateScoreSlot(int score)
{
    this->scoreLabel->setText(QString::number(score)) ;
    this->gameOverPlayer->play() ;
}
