#include "easyview.h"
#include <QDebug>
#include <QIcon>
#include <QResizeEvent>

EasyView::EasyView(QWidget *) {
    resize(800, 533);
    setWindowTitle("简单");

    setAutoFillBackground(true);
    setWindowIcon(QIcon("res/logo-fish.png"));
    //
    setMouseTracking(true);
    this->setBackgroundBrush(QBrush(QPixmap("res/b.png")));

    mScene = new QGraphicsScene();
    mScene->setSceneRect(0, 0, width() - 4, height() - 4);
    this->setScene(mScene);

    mGun = new Gun("res/pao.png", mScene);
    //    mGun->setPos(width() / 2, height());
    //    mScene->addItem(mGun);

    mFish1 = new MyFish("res/fish/1.png", mScene);
    //    mFish1->setPos(0, 100);
    //    mScene->addItem(mFish1);
    //    mFish2 = new MyFish("res/fish/1.png", mScene);
    //    mFish3 = new MyFish("res/fish/1.png", mScene);
    //    mFish4 = new MyFish("res/fish/1.png", mScene);
    //    mFish5 = new MyFish("res/fish/1.png", mScene);

    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, mScene, &QGraphicsScene::advance);
    mTimer->start(50);
}

void EasyView::resizeEvent(QResizeEvent *event) {
    this->setBackgroundBrush(QBrush(QPixmap("res/b.png").scaled(event->size().width(), event->size().height())));
}

void EasyView::mouseMoveEvent(QMouseEvent *event) {
    QPoint p;
    p = event->pos();

    QLine line(this->width() / 2, this->height(), p.x(), p.y());
    QLineF linef(line);
    mGun->setRotation(-(linef.angle() - 90));

    // qDebug("angle:%f\n", -(linef.angle() - 90));
}
