#include "queue.h"
#include <iostream>

using namespace lab;

template <typename T>
Queue<T>::Queue()
{
    this->first = NULL;
    this->last = NULL;
    this->size = 0;
}

template <typename T>
Queue<T>::~Queue(){

}

template <typename T>
void Queue<T>::push(T value){
    TNode<T>* temp = new TNode<T>(value);
    if(this->empty()){
        this->first = temp;
        this->last = temp;
    }else{
        this->last->setNext(temp);
        this->last = temp;
    }

    this->size++;
}

template <typename T>
T Queue<T>::pop(){
    TNode<T>* temp = this->first;
    T value = temp->value;
    this->first = temp->getNext();
    delete temp;
    this->size--;
    return value;
}

template <typename T>
T Queue<T>::front(){
    return this->first->value;
}

template <typename T>
T Queue<T>::back(){
    return this->last->value;
}

template <typename T>
bool Queue<T>::empty(){
    return this->size == 0;
}

#include "queue_types.cpp"
