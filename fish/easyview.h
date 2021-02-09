#ifndef EASYVIEW_H
#define EASYVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>

class EasyView : public QGraphicsView {
    Q_OBJECT
  public:
    explicit EasyView(QWidget *parent = nullptr);

  signals:
  private:
    QGraphicsScene *mScene;

    // QWidget interface
  protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // EASYVIEW_H
