#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "gamewidget.h"
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class MainWidget : public QWidget {
    Q_OBJECT

  public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

  private:
    QLabel *label;

    QVBoxLayout *vBoxLayout;
    QPushButton *btnStart;
    QPushButton *btnSet;
    QPushButton *btnHelp;
    QPushButton *btnQuit;
    GameWidget *gameWidget;

    void startBtnClick();
    void setBtnClick();
    void helpBtnClick();
};
#endif // MAINWIDGET_H
