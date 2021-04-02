#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#include "MyWidget.h"
#include "SingleGame.h"
#include "netgame.h"
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class SelectWidget : public QWidget {
    Q_OBJECT
  public:
    explicit SelectWidget(QWidget *parent = nullptr);

  signals:

  private:
    QPushButton *btnBase;
    QPushButton *btnSingle;
    QPushButton *btnNet;

    MyWidget *_borad;
    QLabel *bg, *bgTitle;
    void initBtns();
};

#endif // SELECTWIDGET_H
