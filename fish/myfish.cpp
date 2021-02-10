#include "myfish.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>

MyFish::MyFish(const QString &filename, QGraphicsScene *scene)
    : MyPixmapItem(filename, scene) {
    setPos(-scene->width() / 2, scene->height() - 33);
}

void MyFish::advance(int) {
    if (mapToScene(0, 0).x() <= 0 || mapToScene(0, 0).x() >= 800 || mapToScene(0, 0).y() >= 800) {
        setPos(mapToScene(0, -1));
    } else {
        int speed = rand() % 10;
        setPos(mapToScene(speed, -2));
    }
}

void MyFish::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    //    char filename[50] = "0";
    //    static int i = 2;
    //    if (i > 62) {
    //        i = 1;
    //    }
    //    sprintf(filename, "res/fish2/%d.png", i++);

    //    bool ret = pix.load(filename);
    //    if (!ret) {
    //        qDebug() << "res not found :" << filename;
    //        return;
    //    }
    MyPixmapItem::paint(painter, option, widget);
}
