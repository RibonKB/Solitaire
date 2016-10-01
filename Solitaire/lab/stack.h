#ifndef STACK_H
#define STACK_H

#include "tnode.h"

namespace lab
{

template <typename T>
class Stack
{
public:
    TNode<T>* first;
    int size;

    Stack();
    ~Stack();

    void push(T);
    T pop();
    T top();
    bool empty();
};

}

#endif // STACK_H
