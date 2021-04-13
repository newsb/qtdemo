#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#include "MyWidget.h"
#include "SingleGame.h"
#include "netgame.h"
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include "mytask.h"
#include <QThread>
class SelectWidget : public QWidget {
    Q_OBJECT
    QThread workerThread;
  public:
    explicit SelectWidget(QWidget *parent = nullptr);
    ~SelectWidget(){
        //QThread并没有new出来，这样在析构时就需要调用QThread::wait()，
        //如果是堆分配的话， 可以通过deleteLater来让线程自杀
        //在逻辑结束后，调用QThread::quit退出线程的事件循环
        workerThread.quit();
        workerThread.wait();
    }
  signals:

  private:
    QPushButton *btnBase;
    QPushButton *btnSingle;
    QPushButton *btnNet;

    MyWidget *_borad;
    QLabel *bg, *bgTitle;
    void initBtns();
    QFont mFont;

    void SendStart(void);
public slots:
    void handleResults(const QString &result);
signals:
    void operate(const QString &x);
};

#endif // SELECTWIDGET_H
