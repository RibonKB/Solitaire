#include "assets.h"
#include <QPixmap>
#include <QString>
#include <iostream>
#include "../lab/list.h"

Assets::Assets()
{

}

QPixmap* Assets::gameWon;
void Assets::init(){
    initCards();
    Assets::gameWon = new QPixmap(QString(":/util/win.png"));
}

lab::List<lab::List<QPixmap>*>* Assets::cards;
QPixmap* Assets::backCard;
void Assets::initCards(){
    int i, j;
    Assets::cards = new lab::List<lab::List<QPixmap>*>();
    for (i = 0; i < 4; i++){
        Assets::cards->addItem(new lab::List<QPixmap>());
        for(j = 0; j < 13; j++){
            QPixmap* aux = new QPixmap(QString(":/frenchcards/%1_%2.png").arg(i).arg(j));
            Assets::cards->get(i)->addItem(*aux);
        }
    }

    Assets::backCard = new QPixmap(QString(":/frenchcards/back.png"));

}
