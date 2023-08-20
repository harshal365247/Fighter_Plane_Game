#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
#include <QObject>

class Health : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Health();
    int decreaseHealth() ;
private:
    int health ;
signals:
    void gameOverSignal() ;
};

#endif // HEALTH_H
