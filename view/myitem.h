#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>
class MyItem : public QGraphicsItem {
  public:
    MyItem(QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
  public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // MYITEM_H
