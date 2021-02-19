#ifndef MYFISH_H
#define MYFISH_H

#include "mypixmapitem.h"

class MyFish : public MyPixmapItem {
  public:
    MyFish(const QString &filename, QGraphicsScene *scene);
    void death();
    // QGraphicsItem interface
  public:
    virtual void advance(int phase) override;

    // QGraphicsItem interface
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // MYFISH_H
