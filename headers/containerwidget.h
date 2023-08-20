#ifndef CONTAINERWIDGET_H
#define CONTAINERWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QKeyEvent>

#include "widget.h"
#include "menuwidget.h"
#include "scoreWidget.h"
#include "gameoverwidget.h"
#include "database.h"

class containerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit containerWidget(QWidget *parent = nullptr);
    ~containerWidget() ;
    QStackedWidget *stackWidget ;
    QHBoxLayout *layoutForStackWidget ;

    Widget *widgetObj ;
    menuWidget *menuWidgetObj ;
    scoreWidget *scoreWidgetObj ;
    gameOverWidget *gameOverWidgetObj ;

    database *scoreDB ;

public slots:
    void openGameWindow() ;
    void openHighScore() ;
    void openMenu() ;
    void closeApp() ;
    void keyPressEvent(QKeyEvent *event) ;
    void gameOverSlot() ;
    void escSlot() ;
signals:
    void getScoreListSignal(QList<int> &scoreList, QList<QString> &playerNameList) ;
    void initScoreWidgetSignal(QList<int> &scoreList, QList<QString> &playerNameList) ;
    void insertScoreSignal(QString playerName, int score) ;
    void resetWidget() ;
    void updateScoreSignal(int score) ;
};

#endif // CONTAINERWIDGET_H
