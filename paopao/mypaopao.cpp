#include "mypaopao.h"
#include "global.h"

MyPaoPao::MyPaoPao(QGraphicsItem *parent)
    :QGraphicsObject(parent)
{
    mPix=new QPixmap(":/res/paopao.png");
    *mPix=mPix->scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE);
    setTransformOriginPoint(boundingRect().center());
}


QColor MyPaoPao::color() {
    return m_color;
}

void MyPaoPao::setColor(QColor color) {
    m_color = color;
    update();
}


QRectF MyPaoPao::boundingRect() const
{
    return QRectF(0, 0, mPix->width(), mPix->height());
}
#include <QPainter>

void MyPaoPao::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing, true);
//    QRadialGradient radial(1.0*w/2, 1.0*h/2, 1.0*w/2, 1.0*w/2, 1.0*h/2);
//    radial.setColorAt(1, Qt::white);
//    radial.setColorAt(0, m_color);
//    painter->setPen(Qt::white);
//    painter->setBrush(radial);
    painter->drawPixmap(0, 0, mPix->width(), mPix->height(),*mPix);
}
