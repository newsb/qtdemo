#include "myitem.h"
#include <QPainter>
#include <QPixmap>
MyItem::MyItem(QGraphicsItem *parent)
    : QGraphicsItem(parent) {}

QRectF MyItem::boundingRect() const { return QRectF(-200, -200, 200, 230); }

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(1, 1, 44, 55, QPixmap(":/res/s.png"));
    //相对于中心的坐标
}
