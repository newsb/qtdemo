#include "mybullet.h"
#include "gun.h"
#include "mynet.h"
#include <QDebug>
#include <QList>
#include <QtMath>

#include <QPainter>
MyBullet::MyBullet(const QString &filename, QGraphicsScene *scene, qreal angle)
    : MyPixmapItem(filename, scene) {
    mScene = scene;
    qreal dx, dy;

    qreal rad;
    rad = angle * 3.14 / 180; //角度转换为弧度
    dx = 220 * qCos(rad);
    dy = 220 * qSin(rad);
    setPos(scene->width() / 2 + dx, scene->height() - dy);
    setRotation(90 - angle);
}

void MyBullet::doColliding() {
    MyNet *net = new MyNet("res/net.png", mScene);
    net->setPos(mapToScene(0, 0));
    delete this;
}

void MyBullet::advance(int) {
    if (mapToScene(0, 0).x() <= 0 || mapToScene(0, 0).x() >= 800 || mapToScene(0, 0).y() <= 0) {
        delete this;
    } else {
        this->setPos(mapToScene(0, -20));
    }
}

void MyBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-pix.width() / 2, -pix.height(), pix);

    if (this->collidingItems().count() > 0) {
        QList<QGraphicsItem *> list = this->collidingItems();
        //        if (list.count() == 1) {

        //            if (Gun *g = dynamic_cast<Gun *>(list.at(0))) {
        //                qDebug() << "hited is gun ";
        //            } else {
        doColliding();
        //                return;
        //            }
        //        }
    }
}
