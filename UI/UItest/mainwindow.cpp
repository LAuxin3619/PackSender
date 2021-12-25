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
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionnewWindow,&QAction::triggered,this,&MainWindow::newMainWindow);
    connect(ui->line11,&QLineEdit::returnPressed,this,&MainWindow::getText);
    connect(ui->line11,&QLineEdit::returnPressed,ui->line11,&QLineEdit::clear);
    connect(ui->pushButtonPrint,&QPushButton::clicked,this,&MainWindow::printText);

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

void MainWindow::getText()
{
    str=ui->line11->text();
}

void MainWindow::printText()
{
    std::cout<<str.toStdString().data()<<std::endl;
}
