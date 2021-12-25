#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void newMainWindow();
    void getText();
    void printText();

private:
    Ui::MainWindow *ui;

    QString str;
};

#endif // MAINWINDOW_H
