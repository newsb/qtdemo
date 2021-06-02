#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>

class MyTCPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTCPServer(QObject *parent = nullptr);
    qintptr mSocketDescriptor;
signals:


    // QTcpServer interface
protected:
    virtual void incomingConnection(qintptr socketDescriptor) override;
};

#endif // MYTCPSERVER_H
