#ifndef FILESEND_H
#define FILESEND_H

#include <QObject>
#include <QTcpSocket>
class FileSend : public QObject
{
    Q_OBJECT
public:
    explicit FileSend(QTcpSocket * sock,QObject *parent = nullptr);

    void connectServer(QString ip,quint16 port);
    void sendfile(QString filePath);

signals:

private:
    QTcpSocket * mSocket;

};

#endif // FILESEND_H
