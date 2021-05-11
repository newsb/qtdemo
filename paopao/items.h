#ifndef ITEMS_H
#define ITEMS_H


#include <QGraphicsObject>

class ColorFulCircle : public QGraphicsObject
{
    //实现属性所用到的宏
        Q_PROPERTY(QColor color MEMBER m_color READ color WRITE setColor NOTIFY colorChanged)
        Q_OBJECT
    public:
        ColorFulCircle(QGraphicsItem *parent = 0);
        ColorFulCircle(int w, int h, QColor color, QGraphicsItem *parent = 0);
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    signals:
        void colorChanged();

    public:
        QColor color();
        void setColor(QColor color);

    protected:
        int w, h;
        QColor m_color;

};

#endif // ITEMS_H
