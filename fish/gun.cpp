#include "gun.h"
#include <QPainter>

Gun::Gun(const QString &filename, QGraphicsScene *scene)
    : MyPixmapItem(filename, scene) {

    this->setPos(scene->width() / 2, scene->height());
}

// QRectF Gun::boundingRect() const { return QRectF(-pix.width() / 2, -pix.height(), pix.width(), pix.height()); }

// void Gun::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
//    painter->drawPixmap(-pix.width() / 2, -pix.height(), pix);
//}
