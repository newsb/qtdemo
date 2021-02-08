#ifndef BIRD_H
#define BIRD_H

#include <QMenu>
#include <QMouseEvent>
#include <QPixmap>
#include <QTimer>
#include <QWidget>

class Bird : public QWidget {
    Q_OBJECT
  public:
    explicit Bird(QWidget *parent = nullptr);
    QPixmap mPix;
    int min = 0;
    int max = 29;
    void running();
    QPoint m_pos;
    bool isMouseDown = false;
    QMenu *m_menu;

    int speedX = 5;

    int speedY = 4;

  private:
    QTimer *mTimer;

  signals:
    void changePix();
    //推拽后主场景应该移动的位置
    void moving(QPoint point);

    // QWidget interface
  protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // BIRD_H
