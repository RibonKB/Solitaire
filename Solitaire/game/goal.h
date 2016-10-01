#ifndef GOAL_H
#define GOAL_H

#include "../lab/stack.h"
#include "frenchcard.h"

class Goal
{
public:
    lab::Stack<FrenchCard*>* cards;
    bool complete;

public:
    Goal();

    bool addCard(FrenchCard *);
};

#endif // GOAL_H
