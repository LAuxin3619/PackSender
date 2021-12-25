#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QTextBlock>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPushButton * btn = new QPushButton("退出",this);
    btn->show();


    connect(btn,&QPushButton::clicked,this,&QWidget::close);
}

Widget::~Widget()
{
    delete ui;
}

