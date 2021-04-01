#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>

#include <QColor>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QPoint>
#include <QResizeEvent>
#include <QtGui>
class DrawWidget : public QWidget {
    Q_OBJECT
  public:
    explicit DrawWidget(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
  signals:
  public slots:
    void setStyle(int);
    void setwidth(int w);
    void setColor(QColor);
    void clear();

  private:
    QPixmap *pix;
    QPoint startPos;
    QPoint endPos;
    int style;
    int weight;
    QColor color;
};

#endif // DRAWWIDGET_H
