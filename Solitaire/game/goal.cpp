#include "goal.h"

#include "../lab/stack.h"
#include "frenchcard.h"

using namespace lab;

Goal::Goal()
{
    this->cards = new Stack<FrenchCard*>();
    this->complete = false;
}

bool Goal::addCard(FrenchCard * card){

    if(this->complete){
        return false;
    }

    if(this->cards->empty()){
        if(card->rank == 0){
            this->cards->push(card);
            return true;
        }else{
            return false;
        }
    }else{
        if(
            card->suit == this->cards->top()->suit &&
            card->rank == this->cards->top()->rank+1
        ){
            this->cards->push(card);

            if(card->rank == 12){
                this->complete = true;
            }

            return true;
        }else{
            return false;
        }
    }
}
