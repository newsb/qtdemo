#include "filesend.h"

FileSend::FileSend(QTcpSocket * sock,QObject *parent) : QObject(parent)
{
    mSocket=sock;
}

void FileSend::connectServer(QString ip, quint16 port)
{

}

void FileSend::sendfile(QString filePath)
{

}
