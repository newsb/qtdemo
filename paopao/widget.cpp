#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::Widget)
      ,gameView(new GameView(parent))
{
    ui->setupUi(this);
    ui->pushButton->setFlat(true);

}

Widget::~Widget()
{
    delete ui;
}

