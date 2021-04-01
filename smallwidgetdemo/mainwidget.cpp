#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget) {
    ui->setupUi(this);
}

MainWidget::~MainWidget() { delete ui; }

void MainWidget::on_pushButton_clicked() {

    ui->widget->setData(32);
    int x = ui->widget->getData();
    qDebug() << x;
}
