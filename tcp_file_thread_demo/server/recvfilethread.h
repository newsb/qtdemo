#ifndef RECVFILETHREAD_H
#define RECVFILETHREAD_H

#include <QThread>
#include <QTcpSocket>

class RecvFileThread : public QThread
{
    Q_OBJECT
public:
    explicit RecvFileThread(QTcpSocket * socket,QObject *parent = nullptr);

signals:
    void recvOver();
private:
    QTcpSocket * mSocket;

protected:
    virtual void run() override;
};

#endif // RECVFILETHREAD_H
