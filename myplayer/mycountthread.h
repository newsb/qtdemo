#ifndef MYCOUNTTHREAD_H
#define MYCOUNTTHREAD_H

#include <QThread>

class MyCountThread : public QThread
{
    Q_OBJECT
public:
    explicit MyCountThread(QObject *parent = nullptr);

signals:
    // 自定义信号, 传递数据 ,通知主线程更新
    void curNumber(int num);


    // QThread interface
protected:
    virtual void run() override;
};

#endif // MYCOUNTTHREAD_H
