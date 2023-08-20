#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class menuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit menuWidget(QWidget *parent = nullptr);
    QVBoxLayout *layoutForMenu ;
    QHBoxLayout  *layoutPlayerName ;
    QVBoxLayout *overallLayout ;

    QWidget *menuHolder ;

    QLineEdit *textEditForName ;
    QLabel *playerNameLabel ;

    QPushButton *startButton ;
    QPushButton *highScoreButton ;
    QPushButton *exitButton ;

    QList<QPushButton*> buttonsList ;

    QMediaPlayer *mediaPlayer ;
    QMediaPlaylist *buttonMusic ;
    int currentIndex = -1 ;

public slots:
    void mouseMoveEvent(QMouseEvent *event) ;
    void textEditedSlot() ;


signals:

};

#endif // MENUWIDGET_H
