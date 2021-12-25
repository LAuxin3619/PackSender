#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(600,400);

    // 创建菜单栏    ！！！最多只能有一个！！！
    QMenuBar *bar = menuBar();
    // 设置菜单栏到窗口上
    setMenuBar(bar);

    // 创建菜单内容
    QMenu *fileMenu = bar->addMenu("文件");
    QMenu *editMenu = bar->addMenu("编辑");


    // 创建菜单项
    QAction *newAction = fileMenu->addAction("新建");
    // 分割符
    fileMenu->addSeparator();

    QAction *openAction = fileMenu->addAction("打开");


    // 工具栏      ！！！可以有多个！！！
    QToolBar *toolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea,toolBar);

    // 设置工具栏内容
    toolBar->addAction(newAction);
    toolBar->addSeparator();
    toolBar->addAction(openAction);

    // 添加工具栏控件
    QPushButton * btn = new QPushButton("abc",this);
    toolBar->addWidget(btn);

}

