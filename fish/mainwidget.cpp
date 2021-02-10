#include "mainwidget.h"
#include <QFile>
#include <QIcon>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent) {
    setFixedSize(800, 533);
    setWindowIcon(QIcon("res/logo-fish.png"));
    setWindowTitle("捕鱼达人");

    //    QFile file;
    //    file.setFileName("zzzhhh.txt");
    //    当前目录为：  "D:\\qtGit2\\build-fish-Desktop_Qt_5_14_2_MinGW_32_bit-Debug\\"
    //    file.open(QIODevice::WriteOnly);
    //    file.write("msg, qstrlen(msg)"); // write to stderr
    //    file.close();

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap("res/background.jpg").scaled(width(), height())));
    this->setPalette(palette);

    this->label = new QLabel(this);
    label->setPixmap(QPixmap("res/logo.png").scaled(166, 33));

    this->btnStart = new QPushButton(this);
    btnStart->setText("开始游戏");
    this->btnStart->setIcon(QIcon("res/start.png"));
    this->btnStart->setIconSize(QSize(55, 55));
    this->btnStart->setFlat(true);
    connect(this->btnStart, &QPushButton::clicked, this, &MainWidget::startBtnClick);

    this->btnSet = new QPushButton(this);
    btnSet->setText("设置");
    this->btnSet->setIcon(QIcon("res/set.png"));
    this->btnSet->setIconSize(QSize(55, 55));
    this->btnSet->setFlat(true);
    connect(this->btnSet, &QPushButton::clicked, this, &MainWidget::setBtnClick);

    this->btnHelp = new QPushButton(this);
    btnHelp->setText("帮助");
    this->btnHelp->setIcon(QIcon("res/help.png"));
    this->btnHelp->setIconSize(QSize(75, 55));
    this->btnHelp->setFlat(true);
    connect(this->btnSet, &QPushButton::clicked, this, &MainWidget::helpBtnClick);

    this->btnQuit = new QPushButton(this);
    btnQuit->setText("退出");
    this->btnQuit->setIcon(QIcon("res/back.png"));
    this->btnQuit->setIconSize(QSize(75, 55));
    this->btnQuit->setFlat(true);
    connect(this->btnQuit, &QPushButton::clicked, this, &MainWidget::close);

    vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(label);
    vBoxLayout->addWidget(btnStart);
    vBoxLayout->addWidget(btnSet);
    vBoxLayout->addWidget(btnHelp);
    vBoxLayout->addWidget(btnQuit);
    vBoxLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(vBoxLayout);

    this->gameWidget = new GameWidget(this);
    this->gameWidget->hide();
}

void MainWidget::startBtnClick() { this->gameWidget->show(); }
void MainWidget::setBtnClick() {}
void MainWidget::helpBtnClick() {}

MainWidget::~MainWidget() {}
