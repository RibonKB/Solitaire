#include "tnode.h"
#include <QPixmap>
#include "list.h"
#include "../game/frenchcard.h"
#include "../game/cardcolumn.h"
#include "../game/goal.h"

template class TNode<QPixmap>;
template class TNode<List<QPixmap>*>;
template class TNode<FrenchCard*>;
template class TNode<CardColumn*>;
template class TNode<Goal*>;
