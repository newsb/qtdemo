#ifndef FILESEND_H
#define FILESEND_H

#include <QObject>
#include <QTcpSocket>
class FileSend : public QObject
{
    Q_OBJECT
public:
    explicit FileSend(QObject *parent = nullptr);

    void connectServer(QString ip,quint16 port,bool useProxy=false,int proxyType=0,
                       QString proxyIp="",quint16 proxyPort=0,QString proxyUsr="",QString proxyPwd="");
    void sendfile(QString filePath);

    void onTestProxyConnection(QString proxyIp,quint16 proxyPort,QString proxyUsr,QString proxyPwd);
signals:
    void connectOK();
    void connectBreak();
    void sendOver();
    void progressChanged(int per);
private:
    QTcpSocket * mSocket;

};

#endif // FILESEND_H
