#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class gameOverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit gameOverWidget(QWidget *parent = nullptr);
    QVBoxLayout *layoutForMenu ;
    QHBoxLayout  *layoutPlayerName ;
    QHBoxLayout *layoutScoreLabel ;
    QVBoxLayout *overallLayout ;

    QWidget *menuHolder ;

    QLabel *gameOverLabel ;

    QLabel *playerNameLabel ;
    QLabel *scoreLabel ;

    QPushButton *MainMenuButton ;

    QList<QPushButton*> buttonsList ;

    QMediaPlayer *mediaPlayer ;
    QMediaPlayer *gameOverPlayer ;
    QMediaPlaylist *gameOverPlaylist ;
    QMediaPlaylist *buttonMusic ;
    int currentIndex = -1 ;

public slots:
    void mouseMoveEvent(QMouseEvent *event) ;
    void updateScoreSlot(int score) ;

signals:

};

#endif // GAMEOVERWIDGET_H
