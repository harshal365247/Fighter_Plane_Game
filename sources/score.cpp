#include <QFont>

#include "score.h"

Score::Score()
{
    this->score = 0 ;
    this->setPlainText("SCORE : " + QString::number(score)) ;
    this->setFont(QFont("times",18)) ;
    this->setDefaultTextColor(Qt::blue) ;
}

void Score::increaseScore()
{
    score++ ;
    this->setPlainText("SCORE : " + QString::number(score)) ;
}

int Score::getScore()
{
    return this->score ;
}
