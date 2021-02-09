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
    mScene->setSceneRect(0, 0, width() - 2, height() - 2);
    this->setScene(mScene);
}

void EasyView::resizeEvent(QResizeEvent *event) {
    this->setBackgroundBrush(QBrush(QPixmap("res/b.png").scaled(event->size().width(), event->size().height())));
}
