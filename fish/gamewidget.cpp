#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent) {
    this->setAutoFillBackground(true);

    setFixedSize(600, 433);
    /* setWindowIcon(QIcon("res/logo-fish.png"));*/
    setWindowTitle("捕鱼达人2");

    this->label = new QLabel("捕鱼达人2", this);
    label->setStyleSheet("QLabel { color: red; }");

    this->btnStart = new QPushButton(this);
    this->btnStart->setIcon(QIcon("res/start.png"));
    this->btnStart->setIconSize(QSize(55, 55));
    this->btnStart->setFlat(true);
    this->btnStart->setFocusPolicy(Qt::NoFocus);
    connect(btnStart, &QPushButton::clicked, this, &GameWidget::startEasy);

    this->btnEasy = new QPushButton(this);
    this->btnEasy->setIcon(QIcon("res/act.png"));
    this->btnEasy->setIconSize(QSize(45, 55));
    this->btnEasy->setFlat(true);
    this->btnEasy->setFocusPolicy(Qt::NoFocus);

    this->btnHard = new QPushButton(this);
    this->btnHard->setIcon(QIcon("res/anchor.png"));
    this->btnHard->setIconSize(QSize(95, 55));
    this->btnHard->setFlat(true);
    this->btnHard->setFocusPolicy(Qt::NoFocus);

    this->btnHelp = new QPushButton(this);
    this->btnHelp->setIcon(QIcon("res/help.png"));
    this->btnHelp->setIconSize(QSize(75, 55));
    this->btnHelp->setFlat(true);
    this->btnHelp->setFocusPolicy(Qt::NoFocus);

    vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(label);
    vBoxLayout->addWidget(btnStart);
    vBoxLayout->addWidget(btnEasy);
    vBoxLayout->addWidget(btnHard);
    vBoxLayout->addWidget(btnHelp);
    vBoxLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(vBoxLayout); //或者在构造方法指定：new QVBoxLayout(this);

    this->btnBack = new QPushButton(this);
    btnBack->setIcon(QIcon("res/back.png"));
    btnBack->setIconSize(QSize(72, 72));
    btnBack->setFlat(true);

    connect(this->btnBack, &QPushButton::clicked, this, &GameWidget::backBtnClick);

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
