#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QTextBlock>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPushButton * btn1 = new QPushButton("退出",this);
    btn1->move(600,400);
    btn1->show();

    QPushButton * btn2 = new QPushButton("打开",this);
    btn2->move(300,400);
    btn2->show();


    connect(btn1,&QPushButton::clicked,this,&QWidget::close);
    connect(btn2,&QPushButton::clicked,this,&Widget::newWidget);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newWidget()
{
    Widget *w = new Widget();
    w->show();
}

