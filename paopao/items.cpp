#include "items.h"

#include <QPainter>

ColorFulCircle::ColorFulCircle(QGraphicsItem *parent)
    :QGraphicsObject(parent) {}

ColorFulCircle::ColorFulCircle(int w, int h, QColor color, QGraphicsItem *parent)
    :QGraphicsObject(parent), w(w), h(h), m_color(color) {}

QRectF ColorFulCircle::boundingRect() const {
    return QRectF(0, 0, w, h);
}

void ColorFulCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing, true);
    QRadialGradient radial(1.0*w/2, 1.0*h/2, 1.0*w/2, 1.0*w/2, 1.0*h/2);
    radial.setColorAt(1, Qt::white);
    radial.setColorAt(0, m_color);
    painter->setPen(Qt::white);
    painter->setBrush(radial);
    painter->drawEllipse(0, 0, w, h);
}

QColor ColorFulCircle::color() {
    return m_color;
}

void ColorFulCircle::setColor(QColor color) {
    m_color = color;
    update();
}
//————————————————
//版权声明：本文为CSDN博主「hao_zong_yin」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/hao_zong_yin/article/details/73826257
