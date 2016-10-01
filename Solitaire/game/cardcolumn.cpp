#include "cardcolumn.h"

#include "../lab/stack.h"
#include "../lab/list.h"

#include "frenchcard.h"


using namespace lab;

CardColumn::CardColumn()
{
    this->hidden = new Stack<FrenchCard*>();
    this->unhidden = new List<FrenchCard*>();
}

bool CardColumn::showTop(){
    if(this->unhidden->empty()){
        this->unhidden->addItem(this->hidden->pop());
        return true;
    }
    return false;
}

bool CardColumn::addCards(lab::Queue<FrenchCard *> *cards){
    if(this->checkValid(cards->front())){
        while(!cards->empty()){
            this->unhidden->addItem(cards->pop());
        }
        return true;
    }
    return false;
}

bool CardColumn::checkValid(FrenchCard * card){
    if(this->unhidden->empty()){
        if(this->hidden->empty() && card->rank == 12){
            return true;
        }
    }else{
        FrenchCard* top = this->unhidden->get(this->unhidden->size-1);
        if(top->rank-1 == card->rank && top->isBlack() == card->isRed()){
            return true;
        }
    }

    return false;
}
