#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::Widget)
      ,gameView(new GameView(parent))
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

