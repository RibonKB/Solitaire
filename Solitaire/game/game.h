#ifndef GAME_H
#define GAME_H

#include "../lab/queue.h"
#include "../lab/stack.h"
#include "../lab/list.h"

#include "frenchcard.h"
#include "cardcolumn.h"
#include "goal.h"


class Game
{
public:
    lab::List<CardColumn*>* columns;
    lab::Stack<FrenchCard*>* pile;
    lab::Stack<FrenchCard*>* preview;
    lab::List<Goal*>* goals;
    enum selectFrom { NONE, PREVIEW, COLUMN, GOAL };
    lab::Queue<FrenchCard*>* selected;
    Game::selectFrom selection;
    int selectionIndex;

public:
    Game();

    void start();
    bool checkWin();

    void flipFromPile();
    void resetPreview();
    bool flipFromColumn(int);
    void selectFromPreview();
    void selectFromColumn(int, int);
    void selectFromGoal(int);

    bool dropOnColumn(int);
    bool dropOnGoal(int);

    void resetSelection();

};

#endif // GAME_H
