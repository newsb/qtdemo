#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
class MyView : public QGraphicsView {
    Q_OBJECT
  public:
    MyView(QWidget *parent = nullptr);
};

#endif // MYVIEW_H
