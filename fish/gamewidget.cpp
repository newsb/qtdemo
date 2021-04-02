#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent) {
    this->setAutoFillBackground(true);

    setFixedSize(800, 533);
    //    setWindowIcon(QIcon("res/Fish_Icon.png"));
    setWindowTitle("捕鱼达人2");

    //    this->label = new QLabel("捕鱼达人2", this);
    //    label->setStyleSheet("QLabel { color: red; }");
    //简单 模式
    this->btnEasy = new QPushButton(this);
    this->btnEasy->setIcon(QIcon("res/easy.png"));
    this->btnEasy->setIconSize(QSize(120, 52));
    this->btnEasy->setFlat(true);
    this->btnEasy->setFocusPolicy(Qt::NoFocus);
    connect(btnEasy, &QPushButton::clicked, this, &GameWidget::startEasy);

    //普通 模式
    this->btnNormal = new QPushButton(this);
    this->btnNormal->setIcon(QIcon("res/normal.png"));
    this->btnNormal->setIconSize(QSize(120, 52));
    this->btnNormal->setFlat(true);
    this->btnNormal->setFocusPolicy(Qt::NoFocus);
    // 困难模式
    this->btnHard = new QPushButton(this);
    this->btnHard->setIcon(QIcon("res/hard.png"));
    this->btnHard->setIconSize(QSize(120, 52));
    this->btnHard->setFlat(true);
    this->btnHard->setFocusPolicy(Qt::NoFocus);
    //返回
    this->btnQuit = new QPushButton(this);
    this->btnQuit->setIcon(QIcon("res/back.png"));
    this->btnQuit->setIconSize(QSize(120, 52));
    this->btnQuit->setFlat(true);
    this->btnQuit->setFocusPolicy(Qt::NoFocus);
    connect(this->btnQuit, &QPushButton::clicked, this, &GameWidget::backBtnClick);

    vBoxLayout = new QVBoxLayout();

    vBoxLayout->addWidget(btnEasy);
    vBoxLayout->addWidget(btnNormal);
    vBoxLayout->addWidget(btnHard);
    vBoxLayout->addWidget(btnQuit);
    vBoxLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(vBoxLayout); //或者在构造方法指定：new QVBoxLayout(this);

    //    QPalette palette;
    //    palette.setBrush(QPalette::Background, QBrush(QPixmap("res/background.png")));
    //    this->setPalette(palette);
}

GameWidget::~GameWidget() {}

void GameWidget::backBtnClick() { this->hide(); }

void GameWidget::startEasy() {
    mEasyView = new EasyView();
    mEasyView->show();
    ((QWidget *)this->parent())->hide();
}
