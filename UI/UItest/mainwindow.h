#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ipmessage.h"
#include "tcpmessage.h"

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

private:
    Ui::MainWindow *ui;

    IpMessage ip;
    TcpMessage tcp;
};

#endif // MAINWINDOW_H
