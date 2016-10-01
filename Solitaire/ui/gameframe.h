#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <QWidget>
#include <QPainter>
#include <QPoint>

#include "game/game.h"
#include "game/cardcolumn.h"
#include "game/goal.h"

class GameFrame : public QWidget
{
    Q_OBJECT
public:
    Game* game;


public:
    explicit GameFrame(QWidget *parent = 0);

    void newGame();

private:
    int m_cardWidth;
    int m_cardHeight;
    int m_top;
    int m_middle;
    QPoint* m_pilePos;
    QPoint* m_previewPos;
    QPoint* m_columnsPos;
    QPoint* m_goalsPos;
    QPoint* m_cursorPos;
    bool m_win;

    void paintPile(QPainter*);
    void paintPreview(QPainter*);
    void paintColumns(QPainter*);
    void paintHiddenColumn(QPainter*, CardColumn*, QPoint);
    void paintUnhiddenColumn(QPainter*, CardColumn*, QPoint);
    void paintGoals(QPainter*);
    void paintGoal(QPainter*, Goal*, QPoint);
    void paintSelection(QPainter *);
    void paintGameWon(QPainter *);

    int getColumnPressed(int);
    int getSubColumnPressed(CardColumn*, int);
    bool isBlankPressed(CardColumn*, int);
    bool isPilePressed(int);
    bool isPreviewPressed(int);
    bool isGoalPressed(int);
    int getGoalPressed(int);

    bool checkElementRelease(QMouseEvent*);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // GAMEFRAME_H
