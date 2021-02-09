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
    this->btnStart->setIcon(QIcon("res/start.png"));
    this->btnStart->setIconSize(QSize(55, 55));
    this->btnStart->setFlat(true);
    connect(this->btnStart, &QPushButton::clicked, this, &MainWidget::startBtnClick);

    vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(label);
    vBoxLayout->addWidget(btnStart);
    vBoxLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(vBoxLayout);

    this->gameWidget = new GameWidget(this);
    this->gameWidget->hide();
}

void MainWidget::startBtnClick() { this->gameWidget->show(); }

MainWidget::~MainWidget() {}
