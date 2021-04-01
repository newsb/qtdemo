#ifndef MYSMALLWIDGET_H
#define MYSMALLWIDGET_H

#include <QWidget>

namespace Ui {
class MySmallWidget;
}

class MySmallWidget : public QWidget {
    Q_OBJECT

  public:
    explicit MySmallWidget(QWidget *parent = nullptr);
    ~MySmallWidget();
    void setData(int val);
    int getData();

  private:
    Ui::MySmallWidget *ui;
};

#endif // MYSMALLWIDGET_H
