#ifndef MYRUNNABLEWORK_H
#define MYRUNNABLEWORK_H

#include <QObject>
#include <QRunnable>

class MyRunnableWork : public QObject ,public QRunnable
{
    Q_OBJECT
public:
    explicit MyRunnableWork(QObject *parent = nullptr) :QObject(parent)
    {
        // 任务执行完毕,该对象自动销毁
        setAutoDelete(true);
    };
    void run() override{}

signals:

};

#endif // MYRUNNABLEWORK_H
