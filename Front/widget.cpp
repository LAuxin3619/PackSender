#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPushButton * btn = new QPushButton("A",this);
    btn->show();

    connect(btn,&QPushButton::clicked,this,&QWidget::close);
}

Widget::~Widget()
{
    delete ui;
}

