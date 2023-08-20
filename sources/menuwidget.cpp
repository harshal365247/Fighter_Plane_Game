#include <QSize>
#include <QShortcut>
#include <QKeySequence>
#include <QList>
#include <QCursor>
#include <QDebug>
#include <QScreen>

#include "menuwidget.h"

menuWidget::menuWidget(QWidget *parent)
    : QWidget{parent}
{
    overallLayout = new QVBoxLayout() ;
    layoutPlayerName = new QHBoxLayout() ;
    layoutForMenu = new QVBoxLayout() ;
    this->setMouseTracking(true) ;

    QRect geometry = this->screen()->availableGeometry() ;
    int height = geometry.height() ;


    buttonMusic = new QMediaPlaylist(this) ;
    buttonMusic->addMedia(QUrl("qrc:/sound/Resources/sound/buttonChange.mp3")) ;
    buttonMusic->setCurrentIndex(0) ;
    buttonMusic->setPlaybackMode(QMediaPlaylist::CurrentItemOnce) ;

    mediaPlayer = new QMediaPlayer(this) ;
    mediaPlayer->setPlaylist(buttonMusic) ;

    playerNameLabel = new QLabel() ;
    playerNameLabel->setText("PLAYER") ;
    playerNameLabel->setFixedSize(QSize(200, 50));
    playerNameLabel->setAlignment(Qt::AlignCenter) ;
    playerNameLabel->setObjectName("playerNameLabel") ;

    textEditForName = new QLineEdit() ;
    textEditForName->setAlignment(Qt::AlignCenter) ;
    textEditForName->setObjectName("textEditForName") ;
    textEditForName->setFixedSize(200, 50) ;

    connect(textEditForName,&QLineEdit::textEdited,this,&menuWidget::textEditedSlot) ;

    layoutPlayerName->setMargin( (int)(height/5.4)) ;
    layoutPlayerName->setSpacing(50) ;
    layoutPlayerName->setAlignment(Qt::AlignCenter) ;
    layoutPlayerName->addStretch() ;
    layoutPlayerName->addWidget(playerNameLabel) ;
    layoutPlayerName->addWidget(textEditForName) ;
    layoutPlayerName->addStretch() ;

    startButton = new QPushButton() ;
    startButton->setFixedSize(QSize(300, 50)) ;
    startButton->setText("START") ;
    startButton->setObjectName("startButton") ;

    highScoreButton = new QPushButton() ;
    highScoreButton->setFixedSize(QSize(300, 50)) ;
    highScoreButton->setText("HIGH SCORE") ;
    highScoreButton->setObjectName("highScoreButton") ;

    exitButton = new QPushButton() ;
    exitButton->setFixedSize(QSize(300, 50)) ;
    exitButton->setText("EXIT") ;
    exitButton->setObjectName("exitButton") ;

    buttonsList.append(startButton) ;
    buttonsList.append(highScoreButton) ;
    buttonsList.append(exitButton) ;

    QShortcut *upShortCut = new QShortcut(QKeySequence(Qt::Key_Up), this) ;
    QShortcut *downShortCut = new QShortcut(QKeySequence(Qt::Key_Down), this) ;

    layoutForMenu->addWidget(startButton) ;
    layoutForMenu->addWidget(highScoreButton) ;
    layoutForMenu->addWidget(exitButton) ;

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

    startButton->setFocus() ;

    layoutForMenu->setAlignment(Qt::AlignCenter) ;
    layoutForMenu->setSpacing(20) ;

    overallLayout->addLayout(layoutPlayerName) ;
    overallLayout->addLayout(layoutForMenu) ;
    overallLayout->addStretch() ;
    overallLayout->setAlignment(Qt::AlignCenter) ;
    this->setLayout(overallLayout) ;

}

void menuWidget::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event) ;
    foreach(QPushButton* i, buttonsList){
        i->clearFocus() ;
    }
    currentIndex = -1 ;
}

void menuWidget::textEditedSlot()
{
    this->textEditForName->setText(this->textEditForName->text().toUpper()) ;
}
