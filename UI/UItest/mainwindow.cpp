#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QWidget>
#include <QTextEdit>
#include <QToolBar>
#include <QAction>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mode(-1)
{
    std::cout<<"mode: "<<mode<<std::endl;

    ui->setupUi(this);

    connect(ui->actionnewWindow,&QAction::triggered,this,&MainWindow::newMainWindow);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newMainWindow()
{
    MainWindow *w = new MainWindow();
    w->show();
}

