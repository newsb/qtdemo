#include "mypixmapitem.h"

#include <QPainter>

MyPixmapItem::MyPixmapItem(const QString &filename, QGraphicsScene *scene) {
    pix.load(filename);

    scene->addItem(this);
}
QRectF MyPixmapItem::boundingRect() const {
    return QRectF(-pix.width() / 2, -pix.height() / 2, pix.width(), pix.height());
}

void MyPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(-pix.width() / 2, -pix.height(), pix);
}
