#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "bird.h"
#include <QTimer>
#include <QWidget>

class MainScene : public QWidget {
    Q_OBJECT

  public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

  private:
    Bird *mBird;

    QPoint m_Auto_Pos;

    QTimer *mTimer;
    // QWidget interface
  protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // MAINSCENE_H
