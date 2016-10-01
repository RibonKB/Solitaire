#ifndef LIST_H
#define LIST_H

#include "tnode.h"

namespace lab
{

template <typename T>
class List
{
public:
    lab::TNode<T>* first;
    lab::TNode<T>* last;
    int size;

    List();
    ~List();

    void addItem(T);
    bool exists(const T&, bool(*)(const T&, const T&));
    T get(int);
    T operator[](int);
    int getSize();
    bool empty();
    //void delItemByValue(T);
    T delItemByIndex(int);
    T delFirst();
    int realSize();

};

}

#endif // LIST_H
