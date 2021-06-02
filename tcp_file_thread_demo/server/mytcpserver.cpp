#include "mytcpserver.h"
#include <QDebug>
MyTCPServer::MyTCPServer(QObject *parent) : QTcpServer(parent)
{

}


void MyTCPServer::incomingConnection(qintptr socketDescriptor)
{
    mSocketDescriptor=socketDescriptor;
    qDebug()<<"incomingConnection:"<<socketDescriptor;
    QTcpServer::incomingConnection(socketDescriptor);
}
