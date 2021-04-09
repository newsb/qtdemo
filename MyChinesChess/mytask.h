#ifndef MYTASK_H
#define MYTASK_H
#include <QObject>

class MyTask: public QObject
{
    Q_OBJECT
public:

    explicit MyTask(QObject *parent = nullptr);
public slots:
    //写一个继承QObject的类，对需要进行复杂耗时逻辑的入口函数声明为槽函数
    //此类在旧线程new出来，不能给它设置任何父对象
    void doTask(const QString &parameter);

signals:
    void resultReady(const QString &result);
};

#endif // MYTASK_H
