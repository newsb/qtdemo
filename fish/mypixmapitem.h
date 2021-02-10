#ifndef MYBIXMAPITEM_H
#define MYBIXMAPITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPixmap>
class MyPixmapItem : public QGraphicsItem {
  public:
    MyPixmapItem(const QString &filename, QGraphicsScene *scene);

  protected:
    QPixmap pix;

    // QGraphicsItem interface
  public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // MYBIXMAPITEM_H
