#ifndef ASSETS_H
#define ASSETS_H

#include <QPixmap>
#include "../lab/list.h"

class Assets
{
public:
    Assets();
    static void init();

public:
    static lab::List<lab::List<QPixmap>*>* cards;
    static QPixmap* backCard;
    static QPixmap* gameWon;

private:
    static void initCards();
};

#endif // ASSETS_H
