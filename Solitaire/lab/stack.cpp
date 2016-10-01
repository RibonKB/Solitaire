#include "stack.h"
#include <iostream>

using namespace lab;

template <typename T>
Stack<T>::Stack(){
    this->size = 0;
    this->first = NULL;
}

template <typename T>
Stack<T>::~Stack(){

}

template <typename T>
void Stack<T>::push(T value){

    TNode<T>* temp = new TNode<T>(value);

    if(this->empty()){
        first = temp;
    }else{
        temp->setNext(this->first);
        this->first = temp;
    }

    this->size++;
}

template <typename T>
T Stack<T>::pop(){
    TNode<T>* temp = this->first;
    T value = temp->value;
    this->first = temp->getNext();
    delete temp;
    this->size--;
    return value;
}

template <typename T>
T Stack<T>::top(){
    return this->first->value;
}

template <typename T>
bool Stack<T>::empty(){
    return this->size == 0;
}

#include "stack_types.cpp"
