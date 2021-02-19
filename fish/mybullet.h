#ifndef MYBULLET_H
#define MYBULLET_H

#include "mypixmapitem.h"
#include <QGraphicsScene>

class MyBullet : public MyPixmapItem {

  public:
    MyBullet(const QString &filename, QGraphicsScene *scene, qreal angle);

    // QGraphicsItem interface
  public:
    virtual void advance(int phase) override;
};

#endif // BULLET_H
