#include "frenchcard.h"
#include <iostream>

FrenchCard::FrenchCard(){}

FrenchCard::~FrenchCard(){}

void FrenchCard::set(int suit, int rank){
    this->suit = suit;
    this->rank = rank;
}

bool FrenchCard::isRed(){
    return (this->suit == FrenchCard::DIAMONDS) || (this->suit == FrenchCard::HEARTS);
}

bool FrenchCard::isBlack(){
    return (this->suit == FrenchCard::CLUBS) || (this->suit == FrenchCard::SPADES);
}
