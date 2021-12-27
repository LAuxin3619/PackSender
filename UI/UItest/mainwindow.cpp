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

    ui->tcpSrc->setValidator(intPortValidator);
    ui->tcpDst->setValidator(intPortValidator);
    ui->udpSrc->setValidator(intPortValidator);
    ui->udpDst->setValidator(intPortValidator);


    // 新建窗口
    connect(ui->actionnewWindow,&QAction::triggered,this,&MainWindow::newMainWindow);
    // IP发包界面
    connect(ui->ipApplyBtn,&QPushButton::clicked,this,&MainWindow::applyIp);
    connect(ui->ipShowBtn,&QPushButton::clicked,this,&MainWindow::printIp);
    connect(ui->checkEquip,&QPushButton::clicked,this,&MainWindow::setEquip);
    // TCP发包界面
    connect(ui->tcpApplyBtn,&QPushButton::clicked,this,&MainWindow::applyTcp);
    connect(ui->tcpShowBtn,&QPushButton::clicked,this,&MainWindow::printTcp);
    // UDP发包界面
    connect(ui->udpApplyBtn,&QPushButton::clicked,this,&MainWindow::applyUdp);
    connect(ui->udpShowBtn,&QPushButton::clicked,this,&MainWindow::printUdp);


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

void MainWindow::printIp()
{
    ip.showIp();
}

void MainWindow::applyTcp()
{
    tcp.tcpSetSrc(ui->tcpSrc->text().toInt());
    tcp.tcpSetDst(ui->tcpDst->text().toInt());
    tcp.tcpSetText(ui->tcpText->text().toStdString());
}

void MainWindow::printTcp()
{
    tcp.showTcp();
}

void MainWindow::applyUdp()
{
    udp.tcpSetSrc(ui->udpSrc->text().toInt());
    udp.tcpSetDst(ui->udpDst->text().toInt());
    udp.tcpSetText(ui->udpText->text().toStdString());
}

void MainWindow::printUdp()
{
    udp.showUdp();
}

void MainWindow::setEquip()
{
    ui->equipList->clear();
    std::string *pstr=ip.ipEquipList();
    while (*pstr!=""){
        const std::string equip = *pstr;
        ui->equipList->addItem(QString::fromStdString(equip),QString::fromStdString(equip));
        pstr++;
    }
}
