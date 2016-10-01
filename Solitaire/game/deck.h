#ifndef DECK_H
#define DECK_H

#include "../lab/list.h"
#include "../lab/queue.h"
#include "frenchcard.h"

class Deck
{
public:
    lab::List<FrenchCard*>* deck;

public:
    Deck();
    ~Deck();

    void shuffle(unsigned int);
    lab::Queue<FrenchCard*>* getDeck();
    void printDeck();
};

#endif // DECK_H
