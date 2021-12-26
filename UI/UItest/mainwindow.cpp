#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ipmessage.h"
#include "tcpmessage.h"
#include <QMainWindow>
#include <QWidget>
#include <QTextEdit>
#include <QToolBar>
#include <QAction>
#include <iostream>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置数字输入框
    QValidator *intValidator = new QIntValidator(this);

    ui->ipVer->setValidator(intValidator);
    ui->ipLen->setValidator(intValidator);
    ui->ipUProto->setValidator(intValidator);
    ui->ipChkSum->setValidator(intValidator);
    ui->ipTTL->setValidator(intValidator);
    ui->ipSrc->setValidator(intValidator);
    ui->ipDst->setValidator(intValidator);

    ui->tcpSrc_txt->setValidator(intValidator);
    ui->tcpDst_txt->setValidator(intValidator);
    ui->tcpSeq_txt->setValidator(intValidator);
    ui->tcpOfst_txt->setValidator(intValidator);
    ui->tcpWin_txt->setValidator(intValidator);
    ui->tcpChk_txt->setValidator(intValidator);

    connect(ui->actionnewWindow,&QAction::triggered,this,&MainWindow::newMainWindow);
    connect(ui->ipApplyBtn,&QPushButton::clicked,this,&MainWindow::applyIp);
    connect(ui->ipShowBtn,&QPushButton::clicked,this,&MainWindow::printIp);
    connect(ui->tcpApplyBtn,&QPushButton::clicked,this,&MainWindow::applyTcp);
    connect(ui->tcpShowBtn,&QPushButton::clicked,this,&MainWindow::printTcp);

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
    ip.ipSetVer(ui->ipVer->text().toInt());
    ip.ipSetLen(ui->ipLen->text().toInt());
    ip.ipSetUProto(ui->ipUProto->text().toInt());
    ip.ipSetChkSum(ui->ipChkSum->text().toInt());
    ip.ipSetTTL(ui->ipTTL->text().toInt());
    ip.ipSetSrc(ui->ipSrc->text().toInt());
    ip.ipSetDst(ui->ipDst->text().toInt());
}

void MainWindow::applyTcp()
{
    tcp.tcpSetSrc(ui->tcpSrc_txt->text().toInt());
    tcp.tcpSetDst(ui->tcpDst_txt->text().toInt());
    tcp.tcpSetSeq(ui->tcpSeq_txt->text().toInt());
    tcp.tcpSetOfst(ui->tcpOfst_txt->text().toInt());
    tcp.tcpSetWin(ui->tcpWin_txt->text().toInt());
    tcp.tcpSetChk(ui->tcpChk_txt->text().toInt());
}

void MainWindow::printIp()
{
    ip.showIp();
}

void MainWindow::printTcp()
{
    tcp.showTcp();
}

