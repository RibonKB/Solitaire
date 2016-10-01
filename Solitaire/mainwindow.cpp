#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameFrame = new GameFrame(ui->centralwidget);
    gameFrame->setGeometry(0,0,780,501);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameFrame;
}

void MainWindow::on_actionNew_Game_triggered()
{
    gameFrame->newGame();
}
