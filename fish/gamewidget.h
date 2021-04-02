#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "easyview.h"
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
class GameWidget : public QWidget {
    Q_OBJECT

  public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

  private:
    //    QLabel *label;
    EasyView *mEasyView;
    QPushButton *btnEasy;
    QPushButton *btnNormal;
    QPushButton *btnHard;
    QPushButton *btnQuit;
    QVBoxLayout *vBoxLayout;

    void backBtnClick();
    void startEasy();
};

#endif // GAMEWIDGET_H
