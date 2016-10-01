#include "deck.h"
#include "../lab/list.h"
#include "../lab/queue.h"
#include "frenchcard.h"
#include <cstdlib>
#include <iostream>

using namespace lab;

Deck::Deck()
{
    int i, j;
    this->deck = new List<FrenchCard*>();
    for(i = 0; i < 4; i++){
        for(j = 0; j < 13; j++){
            FrenchCard* temp = new FrenchCard();
            temp->set(i, j);
            this->deck->addItem(temp);
        }
    }

}

Deck::~Deck(){
    delete this->deck;
}

void Deck::shuffle(unsigned int seed){
    std::srand(seed);
    //Number between 100~400
    int loops = rand() % 100 + 300;
    int i, index, size = this->deck->size;
    for(i = 0; i < loops; i++){
        index = rand() % size;
        FrenchCard* item = this->deck->delItemByIndex(index);
        this->deck->addItem(item);
    }
}

void Deck::printDeck(){
    for(int i = 0; i < this->deck->size; i++){
        std::cout << this->deck->get(i)->suit << "," << this->deck->get(i)->rank << std::endl;
    }
}

Queue<FrenchCard*>* Deck::getDeck(){
    Queue<FrenchCard*>* d = new Queue<FrenchCard*>();
    for(int i = 0; i < this->deck->size; i++){
        d->push(this->deck->get(i));
    }
    return d;
}
