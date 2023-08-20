#include <QScreen>

#include "scorelistitem.h"

scoreListItem::scoreListItem(QString SNo, QString playerName, QString score)
{
    mainLayout = new QHBoxLayout() ;

    QRect geometry = this->screen()->availableGeometry() ;
    int width = geometry.width() ;
    int height = geometry.height() ;

    serialLabel = new QLabel() ;
    serialLabel->setText(SNo) ;
    serialLabel->setObjectName("scoreListSNo") ;

    nameLabel = new QLabel() ;
    nameLabel->setText(playerName) ;
    nameLabel->setObjectName("scoreListNameLabel") ;

    scoreLabel = new QLabel() ;
    scoreLabel->setText(score) ;
    scoreLabel->setObjectName("setScoreLabel") ;

    spacerOne = new QSpacerItem((int)(width/19.2), 0) ;
    spacerTwo = new QSpacerItem((int)(height/10.8), 0) ;

    mainLayout->addWidget(serialLabel) ;
    mainLayout->addSpacerItem(spacerOne) ;
    mainLayout->addWidget(nameLabel) ;
    mainLayout->addSpacerItem(spacerTwo) ;
    mainLayout->addWidget(scoreLabel) ;

    this->setLayout(mainLayout) ;
}
