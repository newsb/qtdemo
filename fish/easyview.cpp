#include "easyview.h"
#include <QIcon>
#include <QResizeEvent>

EasyView::EasyView(QWidget *) {
    resize(800, 533);
    setWindowTitle("简单");

    setAutoFillBackground(true);
    setWindowIcon(QIcon("res/logo-fish.png"));

    this->setBackgroundBrush(QBrush(QPixmap("res/b.png")));

    mScene = new QGraphicsScene();
    mScene->setSceneRect(0, 0, width() - 4, height() - 4);
    this->setScene(mScene);

    mGun = new Gun("res/pao.png", mScene);
    //    mGun->setPos(width() / 2, height());
    //    mScene->addItem(mGun);

    mFish1 = new MyFish("res/fish1.png", mScene);
    //    mFish1->setPos(0, 100);
    //    mScene->addItem(mFish1);
    mFish2 = new MyFish("res/fish2.png", mScene);
    //    mFish2->setPos(60, 200);
    //    mScene->addItem(mFish2);
    mFish3 = new MyFish("res/fish3.png", mScene);
    //    mFish3->setPos(120, 300);
    //    mScene->addItem(mFish3);
    mFish4 = new MyFish("res/fish4.png", mScene);
    //    mFish4->setPos(180, 400);
    //    mScene->addItem(mFish4);
    mFish5 = new MyFish("res/fish5.gif", mScene);
    //    mFish5->setPos(240, 500);
    //    mScene->addItem(mFish5);

    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, mScene, &QGraphicsScene::advance);
    mTimer->start(100);
}

void EasyView::resizeEvent(QResizeEvent *event) {
    this->setBackgroundBrush(QBrush(QPixmap("res/fish.gif").scaled(event->size().width(), event->size().height())));
}
