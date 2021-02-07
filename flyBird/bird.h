#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QMouseEvent>

class Bird : public QWidget
{
    Q_OBJECT
public:
    explicit Bird(QWidget *parent = nullptr);
    QPixmap mPix;
    int min=0;
    int max=29;
    void running();
    QPoint m_pos;

private:
    QTimer * mTimer;

signals:
    void changePix();
    //推拽后主场景应该移动的位置
    void moving(QPoint point);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // BIRD_H
