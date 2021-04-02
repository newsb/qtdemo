#ifndef EASYVIEW_H
#define EASYVIEW_H

#include "gun.h"
#include "myfish.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

class EasyView : public QGraphicsView {
    Q_OBJECT
  public:
    explicit EasyView(QWidget *parent = nullptr);

  signals:
  private:
    QGraphicsScene *mScene;
    Gun *mGun;
    MyFish *mFish1, *mFish2, *mFish3, *mFish4 /*, *mFish5*/;
    QTimer *mTimer;
    // QWidget interface
  protected:
    virtual void resizeEvent(QResizeEvent *event) override;

    // QWidget interface
  protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    // QWidget interface
  protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // EASYVIEW_H
