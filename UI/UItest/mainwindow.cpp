#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ipmessage.h"
#include "tcpmessage.h"
#include <QMainWindow>
#include <QWidget>
#include <QTextEdit>
#include <QToolBar>
#include <QAction>
#include <QString>
#include <iostream>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置端口数字输入框，范围1024~65535
    QValidator *intPortValidator = new QIntValidator(1024,65535,this);

    ui->tcpSrc_txt->setValidator(intPortValidator);
    ui->tcpDst_txt->setValidator(intPortValidator);

    connect(ui->actionnewWindow,&QAction::triggered,this,&MainWindow::newMainWindow);
    connect(ui->ipApplyBtn,&QPushButton::clicked,this,&MainWindow::applyIp);
    connect(ui->ipShowBtn,&QPushButton::clicked,this,&MainWindow::printIp);
    connect(ui->tcpApplyBtn,&QPushButton::clicked,this,&MainWindow::applyTcp);
    connect(ui->tcpShowBtn,&QPushButton::clicked,this,&MainWindow::printTcp);
    connect(ui->checkEquip,&QPushButton::clicked,this,&MainWindow::setEquip);

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

void MainWindow::applyIp()
{
    ip.ipSetSrc(ui->ipSrc->text());
    ip.ipSetDst(ui->ipDst->text());
}

void MainWindow::applyTcp()
{
    tcp.tcpSetSrc(ui->tcpSrc_txt->text().toInt());
    tcp.tcpSetDst(ui->tcpDst_txt->text().toInt());
    tcp.tcpSetText(ui->tcpText->text().toStdString());
}

void MainWindow::printIp()
{
    ip.showIp();
}

void MainWindow::printTcp()
{
    tcp.showTcp();
}

void MainWindow::setEquip()
{
    ui->equipList->clear();
    std::string *pstr=tcp.tcpEquipList();
    while (*pstr!=""){
        ui->equipList->addItem("1","1");
        pstr++;
    }

    ui->equipList->addItem("Equip1","Equip1");
}
