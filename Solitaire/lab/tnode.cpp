#include "tnode.h"
#include <iostream>

using namespace lab;

template <typename T>
TNode<T>::TNode(T value)
{
    this->value = value;
    this->next = NULL;
}

template <typename T>
TNode<T>::~TNode(){}

template <typename T>
void TNode<T>::setNext(TNode* n){
    this->next = n;
}

template <typename T>
TNode<T>* TNode<T>::getNext(){
    return this->next;
}

#include "tnode_types.cpp"
