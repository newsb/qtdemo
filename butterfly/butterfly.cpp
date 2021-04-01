#include "butterfly.h"
#include <math.h>

const static double PI = 3.1416;

Butterfly::Butterfly(QObject *parent)
    : QObject(parent) {
    up = true;
    pix_up.load("up.png");
    pix_down.load("down.png");
    startTimer(100);
}

void Butterfly::timerEvent(QTimerEvent *) {
    //边界控制
    //右边界
    qreal edgex = scene()->sceneRect().right() + boundingRect().width() / 2;
    //上边界
    qreal edgetop = scene()->sceneRect().top() + boundingRect().height() / 2;
    //下边界
    qreal edgebottom = scene()->sceneRect().bottom() + boundingRect().height() / 2;
    //若超出边界，则水平移回左边界
    if (pos().x() >= edgex) {
        setPos(scene()->sceneRect().left(), pos().y());
    }
    if (pos().y() >= edgetop) {
        setPos(pos().x(), scene()->sceneRect().bottom());
    }
    if (pos().y() >= edgebottom) {
        setPos(pos().x(), scene()->sceneRect().top());
    }
    angle += (qrand() % 10) / 20.0;
    qreal dx = fabs(sin(angle * PI) * 10.0);
    qreal dy = (qrand() % 20) - 10.0;
    //随机飞行的路径，dxdy相对于蝴蝶坐标系而言的， 应使用mapToParent映射为场景的坐标系
    setPos(mapToParent(dx, dy));
}

QRectF Butterfly::boundingRect() const {
    qreal adjust = 2;
    return QRectF(-pix_up.width() / 2 - adjust, -pix_up.height() / 2 - adjust, pix_up.width() + adjust * 2,
                  pix_up.height() + adjust * 2);
}

void Butterfly::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    if (up) {
        painter->drawPixmap(boundingRect().topLeft(), pix_up);
        up = !up;
    } else {
        painter->drawPixmap(boundingRect().topLeft(), pix_down);
        up = !up;
    }
}
