#ifndef CARDCOLUMN_H
#define CARDCOLUMN_H

#include "../lab/list.h"
#include "../lab/stack.h"
#include "../lab/queue.h"
#include "frenchcard.h"

class CardColumn
{
public:
    lab::Stack<FrenchCard*>* hidden;
    lab::List<FrenchCard*>* unhidden;

public:
    CardColumn();

    bool showTop();
    bool addCards(lab::Queue<FrenchCard*>*);

private:
    bool checkValid(FrenchCard*);
};

#endif // CARDCOLUMN_H
