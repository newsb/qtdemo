#ifndef FOOD_H
#define FOOD_H
#include <QGraphicsItem>

class Food : public QGraphicsItem
{
public:
//    元素的坐标
    Food(qreal x, qreal y);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QPainterPath shape() const;
private:
    int GD_Type;
};

#endif // FOOD_H
