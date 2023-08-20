#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QKeyEvent>

class scoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit scoreWidget(QWidget *parent = nullptr);

    QVBoxLayout *mainLayout ;
    QHBoxLayout *scoreLabelLayout ;
    QHBoxLayout *scoreListLayout ;
    QHBoxLayout *backButtonLayout ;

    QLabel      *scoreLabel ;
    QListWidget *scoreListWidget ;
    QPushButton *backButton ;

    QMediaPlaylist *buttonMusic ;
    QMediaPlayer *mediaPlayer ;

public slots :
    void initScoreListWidget(QList<int> &scoreList, QList<QString> &playerNameList) ;
    void keyPressEvent(QKeyEvent *event) ;

signals:

};

#endif // SCOREWIDGET_H
