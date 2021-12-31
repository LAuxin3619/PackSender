#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ipmessage.h"
#include "tcpmessage.h"
#include "funcforsend.h"    // 后端实现代码

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
    // TCP发包界面
    connect(ui->tcpApplyBtn,&QPushButton::clicked,this,&MainWindow::applyTcp);
    connect(ui->tcpShowBtn,&QPushButton::clicked,this,&MainWindow::printTcp);
    connect(ui->tcpSendBtn,&QPushButton::clicked,this,&MainWindow::sendTcp);
    // UDP发包界面
    connect(ui->udpApplyBtn,&QPushButton::clicked,this,&MainWindow::applyUdp);
    connect(ui->udpShowBtn,&QPushButton::clicked,this,&MainWindow::printUdp);
    connect(ui->udpSendBtn,&QPushButton::clicked,this,&MainWindow::sendUdp);


}

void uCharCaster(u_char mac[],std::string str)    // string类点分十六进制mac地址转换成u_char类型
{
    char temp_ch[3];
    u_int temp_int[6];
    for (int i=0;i<6;i++)
    {
        strcpy(temp_ch,str.substr(i*3,2).data());
        sscanf(temp_ch,"%x",&temp_int[i]);
        mac[i]=temp_int[i];
    }
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
    uCharCaster(ip.macSrc,ui->macSrc->text().toStdString());
    uCharCaster(ip.macDst,ui->macDst->text().toStdString());
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
    ip.showIp();
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
    ip.showIp();
    udp.showUdp();
}


void MainWindow::sendTcp()
{
    char *device=new char[30];  /*设备名称，和IP地址保持一致*/
    strcpy(device,ip.ipSrc.data());

    char *src_ip_str=new char[30];/*源IP地址*/
    strcpy(src_ip_str,ip.ipSrc.data());

    char *dst_ip_str=new char[30];   /*目的IP地址*/
    strcpy(dst_ip_str,ip.ipDst.data());

    char *message=new char[tcp.tcpTextLen+10];  /*消息内容*/
    strcpy(message,tcp.tcpText.data());

    uint16_t src_port = static_cast<uint16_t>(tcp.tcpSrcPort);  /*源端口号*/
    uint16_t dst_port = static_cast<uint16_t>(tcp.tcpDstPort);   /*目的端口号*/

    // 发送TCP报文
    std::cout<<"Status Code: " << SendTCP(device,src_ip_str,dst_ip_str,ip.macSrc,ip.macDst,message,src_port,dst_port);

    // 释放内存空间
    delete [] device;
    delete [] src_ip_str;
    delete [] dst_ip_str;
    delete [] message;
}

void MainWindow::sendUdp()
{
    char *device=new char[30];  /*设备名称，和IP地址保持一致*/
    strcpy(device,ip.ipSrc.data());

    char *src_ip_str=new char[30];/*源IP地址*/
    strcpy(src_ip_str,ip.ipSrc.data());

    char *dst_ip_str=new char[30];   /*目的IP地址*/
    strcpy(dst_ip_str,ip.ipDst.data());

    u_char src_mac[6];
    for (int i=0;i<6;i++)src_mac[i]=ip.macSrc[i]; /*源mac地址，6个十六进制数*/

    u_char dst_mac[6];  /*目的mac地址*/
    for (int i=0;i<6;i++)dst_mac[i]=ip.macDst[i];

    char *message=new char[tcp.tcpTextLen+10];  /*消息内容*/
    strcpy(message,tcp.tcpText.data());

    uint16_t src_port = tcp.tcpSrcPort;  /*源端口号*/
    uint16_t dst_port = tcp.tcpDstPort;   /*目的端口号*/

    // 发送TCP报文
    SendUDP(device,src_ip_str,dst_ip_str,src_mac,dst_mac,message,src_port,dst_port);

    // 释放内存空间
    delete [] device;
    delete [] src_ip_str;
    delete [] dst_ip_str;
    delete [] message;
}
