#include "game.h"

#include "../lab/list.h"
#include "../lab/queue.h"
#include "../lab/stack.h"

#include "frenchcard.h"
#include "goal.h"
#include "cardcolumn.h"
#include "deck.h"

#include <ctime>

using namespace lab;
using namespace std;

Game::Game()
{
    this->columns = new List<CardColumn*>();
    this->pile = new Stack<FrenchCard*>();
    this->preview = new Stack<FrenchCard*>();
    this->goals = new List<Goal*>();
    this->selected = new Queue<FrenchCard*>();
    this->selection = Game::selectFrom::NONE;
}

void Game::start(){

    Deck* deck = new Deck();
    deck->shuffle(time(0));
    Queue<FrenchCard*>* pile = deck->getDeck();

    //Create the 7 columns of cards
    for(int i = 0; i < 7; i++){
        CardColumn* aux = new CardColumn();
        for(int j = 0; j <= i; j++){
            aux->hidden->push(pile->pop());
        }
        aux->showTop();
        this->columns->addItem(aux);
    }

    //Create the 4 Goals piles
    for(int i = 0; i < 4; i++){
        Goal* aux = new Goal();
        this->goals->addItem(aux);
    }

    //Create the stack-pile of cards
    while(!pile->empty()){
        this->pile->push(pile->pop());
    }

    //Pile and deck aren't needed anymore
    delete pile;
    delete deck;
}

bool Game::checkWin(){
    int completeCount = 0;
    for(int i = 0; i < this->goals->size; i++){
        if(this->goals->get(i)->complete){
            completeCount++;
        }
    }

    return completeCount == 4;
}

void Game::flipFromPile(){
    if(!this->pile->empty()){
        this->preview->push(this->pile->pop());
    }else{
        this->resetPreview();
    }
}

void Game::resetPreview(){
    while(!this->preview->empty()){
        this->pile->push(this->preview->pop());
    }
}

bool Game::flipFromColumn(int index){
    return this->columns->get(index)->showTop();
}

void Game::selectFromPreview(){
    if(!this->preview->empty() && this->selection == Game::selectFrom::NONE){
        this->selected->push(this->preview->pop());
        this->selection = Game::selectFrom::PREVIEW;
    }
}

void Game::selectFromColumn(int columnId, int size){
    CardColumn* aux = this->columns->get(columnId);

    if(aux->unhidden->size >= size && this->selection == Game::selectFrom::NONE){
        int from = aux->unhidden->size - size;
        int to = aux->unhidden->size;

        for(int i = from; i < to; i++){
            this->selected->push(aux->unhidden->delItemByIndex(from));
        }
        this->selectionIndex = columnId;
        this->selection = Game::selectFrom::COLUMN;
    }
}

void Game::selectFromGoal(int goalId){
    Goal* aux = this->goals->get(goalId);
    if(!aux->cards->empty() && this->selection == Game::selectFrom::NONE){
        this->selected->push(aux->cards->pop());
        this->selection = Game::selectFrom::GOAL;
        this->selectionIndex = goalId;
    }
}

bool Game::dropOnColumn(int columnId){
    if(!this->selected->empty()){
        if(this->columns->get(columnId)->addCards(this->selected)){
            this->selection = Game::selectFrom::NONE;
            return true;
        }else{
            return false;
        }
    }
    return false;
}

bool Game::dropOnGoal(int goalId){
    if(this->selected->size == 1){
        if(this->goals->get(goalId)->addCard(this->selected->front())){
            this->selected->pop();
            this->selection = Game::selectFrom::NONE;
            return true;
        }else{
            return false;
        }
    }
    return false;
}

void Game::resetSelection(){

    switch(this->selection){
        case Game::selectFrom::COLUMN:{
            while(!this->selected->empty()){
                this->columns->get(this->selectionIndex)->unhidden->addItem(this->selected->pop());
            }
            break;
        }
        case Game::selectFrom::GOAL:{
            this->goals->get(this->selectionIndex)->cards->push(this->selected->pop());
            break;
        }
        case Game::selectFrom::PREVIEW:{
            this->preview->push(this->selected->pop());
            break;
        }
    case Game::selectFrom::NONE:{
            break;
        }
    }

    this->selection = Game::selectFrom::NONE;

}
