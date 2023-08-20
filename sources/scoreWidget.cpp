#include <QSpacerItem>
#include <QScrollBar>
#include <QPushButton>
#include <QShortcut>
#include <QScreen>
#include <QListWidgetItem>

#include "scoreWidget.h"
#include "scorelistitem.h"

scoreWidget::scoreWidget(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout() ;

    scoreLabelLayout = new QHBoxLayout() ;
    scoreListLayout = new QHBoxLayout() ;
    backButtonLayout = new QHBoxLayout() ;

    QRect geometry = this->screen()->availableGeometry() ;
    int width = geometry.width() ;
    int height = geometry.height() ;

    scoreLabel = new QLabel() ;
    scoreLabel->setText("HIGH SCORE") ;
    scoreLabel->setAlignment(Qt::AlignCenter) ;
    scoreLabel->setObjectName("scoreLabel") ;

    backButton = new QPushButton() ;
    backButton->setText("BACK") ;
    backButton->setObjectName("backButton") ;

    QSpacerItem *mainSpacerItem = new QSpacerItem(0,(int)(height/7.2)) ;
    QSpacerItem *mainSpacerItemBelow = new QSpacerItem(0, (int)(height/5.4)) ;
    QSpacerItem *listSpacerItem = new QSpacerItem( (int)(width/3.84),0) ;
    QSpacerItem *bwLabelAndList = new QSpacerItem(0, 20) ;
    QSpacerItem *bwListAndButton = new QSpacerItem(0, 20) ;

    scoreLabelLayout->addWidget(scoreLabel) ;
    scoreLabelLayout->setAlignment(Qt::AlignCenter) ;

    scoreListWidget = new QListWidget() ;
    scoreListWidget->setObjectName("scoreListWidget") ;
    scoreListWidget->setFocusPolicy(Qt::NoFocus) ;

    scoreListLayout->addSpacerItem(listSpacerItem) ;
    scoreListLayout->addWidget(scoreListWidget) ;
    scoreListLayout->setAlignment(Qt::AlignCenter) ;
    scoreListLayout->addSpacerItem(listSpacerItem) ;

    backButtonLayout->addWidget(backButton) ;
    backButtonLayout->setAlignment(Qt::AlignCenter) ;

    QScrollBar *scoreWidgetBar = scoreListWidget->verticalScrollBar() ;
    scoreWidgetBar->setObjectName("scoreVerticalScroll") ;

    QScrollBar *scoreWidgetBarHor = scoreListWidget->horizontalScrollBar() ;
    scoreWidgetBarHor->setObjectName("ScorehorizontalScroll") ;

    buttonMusic = new QMediaPlaylist(this) ;
    buttonMusic->addMedia(QUrl("qrc:/sound/Resources/sound/buttonChange.mp3")) ;
    buttonMusic->setCurrentIndex(0) ;
    buttonMusic->setPlaybackMode(QMediaPlaylist::CurrentItemOnce) ;

    mediaPlayer = new QMediaPlayer(this) ;
    mediaPlayer->setPlaylist(buttonMusic) ;

    QShortcut *upShortCut = new QShortcut(QKeySequence(Qt::Key_Up), this) ;
    QShortcut *downShortCut = new QShortcut(QKeySequence(Qt::Key_Down), this) ;

    connect(downShortCut, &QShortcut::activated, this, [&](){
        QCursor::setPos(QPoint(-1,-1)) ;
        backButton->setFocus() ;
        if(mediaPlayer->state() == QMediaPlayer::PlayingState){
            mediaPlayer->setPosition(0) ;
        }
        mediaPlayer->play() ;
    }) ;

    connect(upShortCut, &QShortcut::activated, this, [&](){
        QCursor::setPos(QPoint(-1,-1)) ;
        backButton->setFocus() ;
        if(mediaPlayer->state() == QMediaPlayer::PlayingState){
            mediaPlayer->setPosition(0) ;
        }
        mediaPlayer->play() ;
    }) ;

    mainLayout->addSpacerItem(mainSpacerItem) ;
    mainLayout->addLayout(scoreLabelLayout) ;
    mainLayout->addSpacerItem(bwLabelAndList) ;
    mainLayout->addLayout(scoreListLayout) ;
    mainLayout->addSpacerItem(bwListAndButton) ;
    mainLayout->addLayout(backButtonLayout) ;
    mainLayout->addSpacerItem(mainSpacerItemBelow) ;

    this->setLayout(mainLayout) ;
}

void scoreWidget::initScoreListWidget(QList<int> &scoreList, QList<QString> &playerNameList)
{
    scoreListWidget->clear() ;
    for(int i = 0; i < scoreList.size() ; i++){
        QListWidgetItem *item = new QListWidgetItem() ;
        scoreListItem *customItem = new scoreListItem(QString::number(i+1), playerNameList[i], QString::number(scoreList[i]) ) ;
        scoreListWidget->addItem(item) ;
        scoreListWidget->setItemWidget(item, customItem) ;
    }
}

void scoreWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        QPushButton *temp = qobject_cast<QPushButton*>(this->focusWidget()) ;

        if(temp == nullptr)
            return ;

        emit temp->clicked() ;
    }
}
