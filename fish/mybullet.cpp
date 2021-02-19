#include "mybullet.h"
#include <QtMath>
MyBullet::MyBullet(const QString &filename, QGraphicsScene *scene, qreal angle)
    : MyPixmapItem(filename, scene) {
    qreal dx, dy;

    qreal rad;
    rad = angle * 3.14 / 180; //角度转换为弧度
    dx = 80 * qCos(rad);
    dy = 80 * qSin(rad);
    setPos(scene->width() / 2 + dx, scene->height() - dy);
    setRotation(90 - angle);
}

void MyBullet::advance(int) {
    if (mapToScene(0, 0).x() <= 0 || mapToScene(0, 0).x() >= 800 || mapToScene(0, 0).y() <= 0) {
        delete this;
    } else {
        this->setPos(mapToScene(0, -20));
    }
}
