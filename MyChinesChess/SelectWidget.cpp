#include "SelectWidget.h"

#include <QMessageBox>
#include <QVBoxLayout>

SelectWidget::SelectWidget(QWidget *parent)
    : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout;

    btnBase = new QPushButton(this);
    btnBase->setFlat(true);
    btnBase->setText("基本模式");
    btnBase->setGeometry(22, 22, 88, 44);

    connect(btnBase, &QPushButton::clicked, [=]() {
        _borad = new MyWidget();

        _borad->show();
        this->hide();
    });

    btnSingle = new QPushButton(this);
    btnSingle->setFlat(true);
    btnSingle->setText("单人模式");
    btnSingle->setGeometry(22, 66, 88, 44);
    connect(btnSingle, &QPushButton::clicked, [=]() {
        _borad = new SingleGame();

        _borad->show();
        this->hide();
    });

    btnNet = new QPushButton(this);
    btnNet->setFlat(true);
    btnNet->setText("网络模式");
    btnNet->setGeometry(22, 22, 110, 44);
    connect(btnSingle, &QPushButton::clicked, [=]() {
        //    网络 + 2人
        bool bServer = false;
        QMessageBox::StandardButton ret = QMessageBox::question(nullptr, "server or client?", "作为服务器启动？");
        if (ret == QMessageBox::Yes) {
            bServer = true;
        }
        _borad = new NetGame(bServer);
        _borad->show();
        this->hide();
    });

    layout->addWidget(btnBase);
    layout->addWidget(btnSingle);
    layout->addWidget(btnNet);
    this->setLayout(layout);

    this->setStyleSheet("QPushButton {font-size: 55px;color: red}");
}
