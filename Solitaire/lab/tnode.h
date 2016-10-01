#ifndef TNODE_H
#define TNODE_H

namespace lab
{

template <typename T>
class TNode
{
public:
    T value;
    TNode<T>* next;

    TNode(T);
    ~TNode();

    void setNext(TNode*);
    TNode* getNext();

};

}

#endif // TNODE_H
