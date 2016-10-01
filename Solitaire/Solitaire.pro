#-------------------------------------------------
#
# Project created by QtCreator 2016-09-29T16:36:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Solitaire
TEMPLATE = app


SOURCES += main.cpp\
    assets/assets.cpp \
    game/deck.cpp \
    game/frenchcard.cpp \
    lab/list.cpp \
    lab/list_types.cpp \
    lab/queue.cpp \
    lab/queue_types.cpp \
    lab/stack.cpp \
    lab/stack_types.cpp \
    lab/tnode.cpp \
    lab/tnode_types.cpp \
    game/game.cpp \
    game/cardcolumn.cpp \
    game/goal.cpp \
    mainwindow.cpp \
    ui/gameframe.cpp

HEADERS  += \
    assets/assets.h \
    game/deck.h \
    game/frenchcard.h \
    lab/list.h \
    lab/queue.h \
    lab/stack.h \
    lab/tnode.h \
    game/game.h \
    game/cardcolumn.h \
    game/goal.h \
    mainwindow.h \
    ui/gameframe.h

RESOURCES += \
    assets/assets.qrc

FORMS += \
    mainwindow.ui
