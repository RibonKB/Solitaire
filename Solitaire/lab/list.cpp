#include "list.h"
#include "tnode.h"
#include <iostream>

using namespace lab;
using namespace std;

template <typename T>
List<T>::List()
{
    this->size = 0;
    this->first = NULL;
    this->last = NULL;
}

template <typename T>
List<T>::~List(){}

template <typename T>
void List<T>::addItem(T value){
    TNode<T>* temp = new TNode<T>(value);
    if(this->last == NULL){
        this->last = this->first = temp;
    }else{
        this->last->setNext(temp);
        this->last = temp;
    }
    this->size++;
}

template <typename T>
bool List<T>::exists(T const &value, bool(*cmp)(const T &, const T &)){
    TNode<T>* temp = this->first;
    while(temp != NULL){
        if(cmp(temp->value, value)){
            return true;
        }
        temp = temp->getNext();
    }
    return true;
}

template <typename T>
T List<T>::get(int index){
    if(index > (this->size)-1){
        cerr << "Error: Index out of bounds" << endl;
        return T();
    }
    TNode<T>* temp = this->first;
    int actual = 0;
    while(actual < index){
        temp = temp->getNext();
        actual++;
    }
    return temp->value;
}

template <typename T>
int List<T>::getSize(){
    return this->size;
}

template <typename T>
bool List<T>::empty(){
    return this->size == 0;
}

//template <typename T>
//void List<T>::delItemByValue(T value){

//}

template <typename T>
T List<T>::delItemByIndex(int index){
    TNode<T>* prev = NULL;
    TNode<T>* curr = this->first;
    int actual = 0;

    while(actual < index and curr != NULL){
        prev = curr;
        curr = curr->getNext();
        actual++;
    }

    if(index == 0){
        this->first = curr->getNext();
    }else{
        prev->setNext(curr->getNext());
    }

    if(index == (this->size -1)){
        this->last = prev;
    }

    T value = curr->value;
    delete curr;

    this->size--;

    return value;

}

template <typename T>
T List<T>::delFirst(){
    TNode<T>* temp = this->first;
    this->first = temp->getNext();
    T value = temp->value;
    delete temp;
    return value;
}

template <typename T>
int List<T>::realSize(){
    int size = 0;
    TNode<T>* curr = this->first;
    while(curr != NULL){
        size++;
        curr = curr->getNext();
    }
    return size;
}

#include "list_types.cpp"
