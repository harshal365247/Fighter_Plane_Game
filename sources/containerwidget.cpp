#include <QPushButton>
#include <QShortcut>
#include <QMessageBox>

#include "containerwidget.h"

containerWidget::containerWidget(QWidget *parent)
    : QWidget{parent}
{
    layoutForStackWidget = new QHBoxLayout() ;
    stackWidget = new QStackedWidget() ;

    scoreWidgetObj = new scoreWidget() ;
    widgetObj = new Widget() ;
    menuWidgetObj = new menuWidget() ;
    menuWidgetObj->setObjectName("menuWidget") ;
    scoreDB = new database() ;
    gameOverWidgetObj = new gameOverWidget() ;
    gameOverWidgetObj->setObjectName("menuWidget") ;

    QShortcut *escShortCut = new QShortcut(QKeySequence(Qt::Key_Escape), this) ;

    connect(menuWidgetObj->startButton, &QPushButton::clicked, this, &containerWidget::openGameWindow) ;
    connect(menuWidgetObj->highScoreButton, &QPushButton::clicked, this, &containerWidget::openHighScore) ;
    connect(menuWidgetObj->exitButton, &QPushButton::clicked, this, &containerWidget::closeApp) ;
    connect(this,SIGNAL(getScoreListSignal(QList<int>&,QList<QString>&)),scoreDB, SLOT(getScoreList(QList<int>&,QList<QString>&))) ;
    connect(this, SIGNAL(initScoreWidgetSignal(QList<int>&,QList<QString>&)), scoreWidgetObj, SLOT(initScoreListWidget(QList<int>&,QList<QString>&))) ;
    connect(widgetObj->health, &Health::gameOverSignal, this, &containerWidget::gameOverSlot) ;
    connect(this, &containerWidget::insertScoreSignal, scoreDB, &database::InsertScore) ;
    connect(scoreWidgetObj->backButton, &QPushButton::clicked, this, &containerWidget::openMenu) ;
    connect(this, &containerWidget::resetWidget, widgetObj, &Widget::stopGame) ;
    connect(this, SIGNAL(updateScoreSignal(int)), gameOverWidgetObj, SLOT(updateScoreSlot(int)) ) ;
    connect(gameOverWidgetObj->MainMenuButton, &QPushButton::clicked, this, &containerWidget::openMenu) ;
    connect(escShortCut, &QShortcut::activated, this, &containerWidget::escSlot) ;


    stackWidget->addWidget(widgetObj) ;
    stackWidget->addWidget(menuWidgetObj) ;
    stackWidget->addWidget(scoreWidgetObj) ;
    stackWidget->addWidget(gameOverWidgetObj) ;

    this->openMenu() ;

    layoutForStackWidget->addWidget(stackWidget) ;
    this->setLayout(layoutForStackWidget) ;
}

containerWidget::~containerWidget()
{
    scoreDB->local_db.close() ;
    delete scoreDB ;
}

void containerWidget::openGameWindow()
{
    this->widgetObj->playerNameString = this->menuWidgetObj->textEditForName->text() ;
    this->widgetObj->setMouseTracking(false) ;

    if(this->widgetObj->playerNameString.isEmpty()){
        QMessageBox::information(this,tr("Enter Name"),tr("Player name cannot be empty. Please enter player name.")) ;
        return ;
    }
    QString left = QString::fromUtf8(u8"\u2190") ;
    QString up = QString::fromUtf8(u8"\u2191") ;
    QString right = QString::fromUtf8(u8"\u2192") ;
    QString spaceBar = QString::fromUtf8(u8"\u2423") ;

    QMessageBox::information(this,tr("Controls"),QString("Use Arrow keys ( " + left + up + right + " ) to move the plane. \nUse space bar ( " + spaceBar + " ) to shoot bullets.")) ;

    emit this->widgetObj->startGameSignal() ;
    connect(widgetObj->health, &Health::gameOverSignal, this, &containerWidget::gameOverSlot) ;
    this->stackWidget->setCurrentWidget(widgetObj) ;
}

void containerWidget::openHighScore()
{
   QList<QString> playerNameList ;
   QList<int> scoreList ;

   emit getScoreListSignal(scoreList, playerNameList) ;
   emit initScoreWidgetSignal(scoreList, playerNameList) ;

   this->stackWidget->setCurrentWidget(scoreWidgetObj) ;
}

void containerWidget::openMenu()
{
    stackWidget->setCurrentWidget(menuWidgetObj) ;
}

void containerWidget::closeApp()
{
    if(QMessageBox::question
            (this,tr("Quit?"),tr("Are you sure, you want to quit the game?"),
             QMessageBox::Yes|QMessageBox::No,QMessageBox::No)
            == QMessageBox::No)
        return ;

    this->close() ;
}

void containerWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        QPushButton *temp = nullptr ;
        if(this->stackWidget->currentWidget() == menuWidgetObj) temp = qobject_cast<QPushButton*>(this->menuWidgetObj->focusWidget()) ;
        if(this->stackWidget->currentWidget() == gameOverWidgetObj) temp = qobject_cast<QPushButton*>(this->gameOverWidgetObj->focusWidget()) ;

        if(temp == nullptr)
            return ;

        emit temp->clicked() ;
    }
}

void containerWidget::gameOverSlot()
{
    emit insertScoreSignal(widgetObj->playerNameObj->getPlayerName(), widgetObj->score->getScore()) ;
    emit updateScoreSignal(widgetObj->score->getScore()) ;
    emit resetWidget() ;
    this->stackWidget->setCurrentWidget(gameOverWidgetObj) ;
}

void containerWidget::escSlot()
{
    if(stackWidget->currentWidget() == menuWidgetObj){
        emit menuWidgetObj->exitButton->clicked() ;
    }
    else if(stackWidget->currentWidget() == gameOverWidgetObj){
        stackWidget->setCurrentWidget(menuWidgetObj) ;
    }
    else if(stackWidget->currentWidget() == widgetObj){
        emit widgetObj->health->gameOverSignal() ;
    }
    else if(stackWidget->currentWidget() == scoreWidgetObj){
        emit scoreWidgetObj->backButton->clicked() ;
    }

    return ;
}

