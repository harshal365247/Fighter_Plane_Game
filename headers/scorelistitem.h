#ifndef SCORELISTITEM_H
#define SCORELISTITEM_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>

class scoreListItem : public QWidget
{
    Q_OBJECT
public:
    scoreListItem(QString SNo, QString playerName, QString score);
    QHBoxLayout *mainLayout ;
    QSpacerItem *spacerOne ;
    QSpacerItem *spacerTwo ;
    QLabel *serialLabel ;
    QLabel *nameLabel ;
    QLabel *scoreLabel ;

};

#endif // SCORELISTITEM_H
