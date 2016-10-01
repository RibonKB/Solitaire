#include "gameframe.h"
#include "game/game.h"
#include <QPainter>
#include <Qt>
#include <algorithm>

#include "assets/assets.h"
#include "game/frenchcard.h"
#include "game/cardcolumn.h"
#include "game/goal.h"

#include "lab/queue.h"

#include <iostream>
#include <QMouseEvent>

GameFrame::GameFrame(QWidget *parent) : QWidget(parent)
{

    this->setFocusPolicy(Qt::StrongFocus);

    Assets::init();
    this->m_cardWidth = Assets::backCard->width();
    this->m_cardHeight = Assets::backCard->height();

    this->m_top = 10;
    this->m_middle = this->m_top + this->m_cardHeight + 20;

    this->m_pilePos = new QPoint(10, this->m_top);
    this->m_previewPos = new QPoint(this->m_pilePos->x() + this->m_cardWidth + 10, this->m_top);
    this->m_goalsPos = new QPoint(this->m_previewPos->x() + this->m_cardWidth*2 + 20, this->m_top);
    this->m_columnsPos = new QPoint(10, this->m_middle);
    this->m_cursorPos = new QPoint(0,0);

    this->game = 0;

}

void GameFrame::newGame(){
    this->m_win = false;
    this->game = new Game();
    this->game->start();
    update();
}

void GameFrame::paintEvent(QPaintEvent *){

    if(this->game == 0){
        return;
    }

    QPainter* painter = new QPainter(this);

    if(this->m_win){
        paintGameWon(painter);
        painter->end();
        delete painter;
        return;
    }

    paintPile(painter);
    paintPreview(painter);
    paintColumns(painter);
    paintGoals(painter);
    paintSelection(painter);

    painter->end();
    delete painter;
}

void GameFrame::paintPile(QPainter * p){
    if(!this->game->pile->empty()){
        p->drawPixmap(*this->m_pilePos, *Assets::backCard);
    }
}

void GameFrame::paintPreview(QPainter * p){
    if(!this->game->preview->empty()){
        FrenchCard* aux = this->game->preview->top();
        p->drawPixmap(*this->m_previewPos, Assets::cards->get(aux->suit)->get(aux->rank));
    }
}

void GameFrame::paintColumns(QPainter * p){
    QPoint pos = *this->m_columnsPos;
    int size = this->game->columns->size;
    for(int i = 0; i < size; i++){
        CardColumn* aux = this->game->columns->get(i);

        if(!aux->hidden->empty()){
            this->paintHiddenColumn(p, aux, pos);
        }

        if(!aux->unhidden->empty()){
            this->paintUnhiddenColumn(p, aux, pos);
        }

        pos += QPoint(this->m_cardWidth + 10, 0);
    }
}

void GameFrame::paintHiddenColumn(QPainter* p, CardColumn* column, QPoint pos){
    int size = column->hidden->size;
    for(int i = 0; i < size; i++){
        p->drawPixmap(pos, *Assets::backCard);
        pos += QPoint(0, 10);
    }
}

void GameFrame::paintUnhiddenColumn(QPainter* p, CardColumn* column, QPoint pos){
    pos += QPoint(0, 10 * column->hidden->size);
    int size = column->unhidden->size;
    for(int i = 0; i < size; i++){
        FrenchCard* caux = column->unhidden->get(i);
        p->drawPixmap(pos, Assets::cards->get(caux->suit)->get(caux->rank));
        pos += QPoint(0, 20);
    }
}

void GameFrame::paintGoals(QPainter * p){
    QPoint pos = *this->m_goalsPos;
    int size = this->game->goals->size;
    for(int i = 0; i < size; i++){
        Goal* aux = this->game->goals->get(i);
        if(!aux->cards->empty()){
            this->paintGoal(p, aux, pos);
        }
        pos += QPoint(this->m_cardWidth + 10, 0);
    }
}

void GameFrame::paintGoal(QPainter* p, Goal* goal, QPoint pos){
    FrenchCard* caux = goal->cards->top();
    p->drawPixmap(pos, Assets::cards->get(caux->suit)->get(caux->rank));
}

void GameFrame::paintSelection(QPainter *p){
    if(this->game->selection != Game::selectFrom::NONE){
        p->drawPixmap(*this->m_cursorPos, Assets::cards->get(this->game->selected->front()->suit)->get(this->game->selected->front()->rank));
    }
}

void GameFrame::paintGameWon(QPainter *p){
    p->drawPixmap(0,0,*Assets::gameWon);
}

void GameFrame::mousePressEvent(QMouseEvent *event){
    //If click "y" position is more than middle, the click was on columns area

    if(this->game == 0){
        return;
    }

    this->m_cursorPos->setX(event->x());
    this->m_cursorPos->setY(event->y());

    update();

    if(event->y() > this->m_middle){
        int index = this->getColumnPressed(event->x());
        if(index < 7){
            CardColumn* aux = this->game->columns->get(index);
            if(!aux->unhidden->empty()){
                int subColumnSize = this->getSubColumnPressed(aux, event->y() - this->m_middle);
                if(subColumnSize > 0){
                    this->game->selectFromColumn(index,subColumnSize);
                }
            }else if(!aux->hidden->empty()){
                if(this->isBlankPressed(aux, event->y() - this->m_middle)){
                    aux->showTop();
                }
            }
        }
    }//Otherwise the click was on another board area
    else{
        if(this->isPilePressed(event->x())){
            this->game->flipFromPile();
            return;
        }
        if(this->isPreviewPressed(event->x())){
            this->game->selectFromPreview();
            return;
        }
        if(this->isGoalPressed(event->x())){
            int index = this->getGoalPressed(event->x() - (40 + this->m_cardWidth*3));
            this->game->selectFromGoal(index);
            return;
        }
    }
}

int GameFrame::getColumnPressed(int x){
    return (int)((x*7)/770);
}

int GameFrame::getSubColumnPressed(CardColumn * column, int depth){
    int hiddenDepth = column->hidden->size * 10;
    int unhiddenDepth = (column->unhidden->size-1)*20 + this->m_cardHeight + hiddenDepth;
    if(depth < hiddenDepth || depth > unhiddenDepth){
        return 0;
    }
    int offset = (int)(std::min((depth - hiddenDepth), column->unhidden->size * 20 -1) / 20);
    return column->unhidden->size - offset;
}

bool GameFrame::isBlankPressed(CardColumn * column, int depth){
    int hiddenDepth = (column->hidden->size-1)*10 + this->m_cardHeight;
    if(depth > hiddenDepth){
        return false;
    }
    return true;
}

bool GameFrame::isPilePressed(int offset){
    return offset < 10 + this->m_cardWidth && offset > 10;
}

bool GameFrame::isPreviewPressed(int offset){
    return offset < 20 + this->m_cardWidth*2;
}

bool GameFrame::isGoalPressed(int offset){
    return (offset > (40 + this->m_cardWidth*3)) && offset < 770;
}

int GameFrame::getGoalPressed(int offset){
    int total = 4*this->m_cardWidth + 30;
    return (int) ((offset*4)/total);
}

void GameFrame::mouseMoveEvent(QMouseEvent *event){
    this->m_cursorPos->setX(event->x());
    this->m_cursorPos->setY(event->y());
    update();
}

void GameFrame::mouseReleaseEvent(QMouseEvent *event){

    if(this->game == 0){
        return;
    }

    if(this->game->selection == Game::selectFrom::NONE){
        return;
    }

    if(!checkElementRelease(event)){
       this->game->resetSelection();
    }

    update();
}

bool GameFrame::checkElementRelease(QMouseEvent * event){
    //Dragged Element(s) was released over columns area
    if(event->y() > this->m_middle){
        int index = this->getColumnPressed(event->x());
        if(index < 7){
            return this->game->dropOnColumn(index);
        }
    }//Dragged element(s) was released in another board area
    else{
        if(this->isGoalPressed(event->x())){
            int index = this->getGoalPressed(event->x() - (40 + this->m_cardWidth*3));
            if(this->game->dropOnGoal(index)){
                if(this->game->checkWin()){
                    this->m_win = true;
                }
            }
        }
    }

    return false;
}
