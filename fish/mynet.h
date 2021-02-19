#ifndef MYNET_H
#define MYNET_H

#include "mypixmapitem.h"

class MyNet : public MyPixmapItem {
  public:
    MyNet(const QString &filename, QGraphicsScene *scene);

    // QGraphicsItem interface
  public:
    virtual void advance(int phase) override;
};

#endif // MYNET_H
