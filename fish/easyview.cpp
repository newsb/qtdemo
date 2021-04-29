#include "easyview.h"
#include "mybullet.h"
#include <QDebug>
#include <QIcon>
#include <QResizeEvent>

EasyView::EasyView(QWidget *) {
    setFixedSize(800, 533);
    setWindowTitle("简单");

    setAutoFillBackground(true);
    setWindowIcon(QIcon("res/Fish_Icon.png"));
    //
    setMouseTracking(true);
    this->setBackgroundBrush(QBrush(QPixmap("res/seaworld.png")));

    mScene = new QGraphicsScene();
    mScene->setSceneRect(0, 0, width() - 4, height() - 4);
    this->setScene(mScene);

    mGun = new Gun("res/pao5.png", mScene);
    //    mGun->setPos(width() / 2, height());
    //    mScene->addItem(mGun);

    mFish1 = new MyFish("res/shark_r1.png", mScene);
    //    mFish1->setPos(0, 100);
    //    mScene->addItem(mFish1);
    mFish2 = new MyFish("res/shark_r2.png", mScene);
    mFish3 = new MyFish("res/shark_r3.png", mScene);
    mFish4 = new MyFish("res/shark_r4.png", mScene);

    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, mScene, &QGraphicsScene::advance);
    mTimer->start(100);
}

void EasyView::resizeEvent(QResizeEvent *event) {
    this->setBackgroundBrush(QBrush(QPixmap("res/seaworld.png").scaled(event->size().width(), event->size().height())));
    mScene->setSceneRect(0, 0, event->size().width() - 4, event->size().height() - 4);
    //    mGun->setPos(event->size().width() / 2, event->size().height());
    mGun->setPos(mScene->width() / 2, mScene->height());
}

void EasyView::mouseMoveEvent(QMouseEvent *event) {
    QPoint p;
    p = event->pos();

    QLine line(this->width() / 2, this->height(), p.x(), p.y());
    QLineF linef(line);
    mGun->setRotation(-(linef.angle() - 90));

    // qDebug("angle:%f\n", -(linef.angle() - 90));
}

void EasyView::mousePressEvent(QMouseEvent *event) {
    QPoint p = event->pos();
    QLineF linef(width() / 2, height(), p.x(), p.y());
    //MyBullet *bullet =
    new MyBullet("res/B5.png", mScene, linef.angle());
}
