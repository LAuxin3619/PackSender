#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ipmessage.h"
#include "tcpmessage.h"

typedef TcpMessage UdpMessage; // Tcp与Udp类传递相同的参数

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

public slots:
    void newMainWindow();
    void applyIp();
    void printIp();
    void applyTcp();
    void printTcp();
    void applyUdp();
    void printUdp();
    void sendTcp();
    void sendUdp();

private:
    Ui::MainWindow *ui;

    IpMessage ip;
    TcpMessage tcp;
    UdpMessage udp;
};

#endif // MAINWINDOW_H
