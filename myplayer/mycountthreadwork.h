#ifndef MYCOUNTTHREADWORK_H
#define MYCOUNTTHREADWORK_H

#include <QObject>

class MyCountThreadWork : public QObject
{
    Q_OBJECT
public:
    explicit MyCountThreadWork(QObject *parent = nullptr);
    void working();

signals:
    void curNumber(int num);

};

#endif // MYCOUNTTHREADWORK_H
