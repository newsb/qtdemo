#ifndef MAPWIDGET_H
#define MAPWIDGET_H
#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
class MapWidget : public QGraphicsView {
    Q_OBJECT
  public:
    MapWidget();
    void readMap();
    //映射场景坐标和地图坐标
    QPointF mapToMap(QPointF);
  public slots:
    void slotZoom(int);

  protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void mouseMoveEvent(QMouseEvent *event) override;

  private:
    QPixmap map;
    qreal zoom;
    QLabel *viewCoord;
    QLabel *sceneCoord;
    QLabel *mapCoord;
    double x1, y1, x2, y2;
};

#endif // MAPWIDGET_H
