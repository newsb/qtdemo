#include "SelectWidget.h"

#include <QMessageBox>
#include <QVBoxLayout>

SelectWidget::SelectWidget(QWidget *parent)
    : QWidget(parent) {

    setFixedSize(800, 600);
    bg = new QLabel(this);
    bg->setGeometry(0, 0, 800, 600);
    bg->setPixmap(QPixmap(":/res/bg.jpg").scaled(this->width(), this->height()));

    QVBoxLayout *layout = new QVBoxLayout;

    bgTitle = new QLabel(this);
    bgTitle->setGeometry(0, 0, 400, 145);
    bgTitle->setPixmap(QPixmap(":/res/2.png").scaled(400, 145));
    bgTitle->move(this->width() / 2 - bgTitle->width() / 2, 30);
    initBtns();

    //    layout->addWidget(bgTitle);

    //    layout->addSpacing(77);
    layout->addWidget(btnBase);
    layout->addWidget(btnSingle);
    layout->addWidget(btnNet);
    layout->setAlignment(Qt::AlignBottom);
    layout->setMargin(20);
    layout->setSpacing(20);

    //    layout->setGeometry(QRect(300, 160, 200, 107));
    this->setLayout(layout);

    this->setStyleSheet("QPushButton {font-family: 微软雅黑;font-size: 56px;color: #f16c4d}");
}

void SelectWidget::initBtns() {
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
    connect(btnNet, &QPushButton::clicked, [=]() {
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
}
