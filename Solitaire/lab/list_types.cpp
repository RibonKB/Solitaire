#include "list.h"
#include <QPixmap>
#include "../game/frenchcard.h"
#include "../game/cardcolumn.h"
#include "../game/goal.h"

using namespace lab;

template class List<QPixmap>;
template class List<List<QPixmap>*>;
template class List<FrenchCard*>;
template class List<CardColumn*>;
template class List<Goal*>;
