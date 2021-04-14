#include "netgame.h"
#include <QDebug>
#include <QMessageBox>

NetGame::NetGame(bool isServer) {
    _server = nullptr;
    _socket = nullptr;
    if (isServer) {
        _server = new QTcpServer(this);
        _server->listen(QHostAddress::Any, 9999);
        connect(_server, &QTcpServer::newConnection, [=]() {
            //只接受一个连接
            if (_socket) return;
            _socket = _server->nextPendingConnection();
            connect(_socket, &QTcpSocket::readyRead, this, &NetGame::slotRecv);
            connect(_socket, &QTcpSocket::disconnected,[&](){
                mConnected=false;
            });

            qDebug() << "connect";
            mConnected=true;
            char buf[2];
            buf[0] = 1;
            buf[1] = 0; //服务器执红
            //服务器发送给客户端信息
            _socket->write(buf, 2);
            init(buf[1] == 0);
        });
    } else {
        _socket = new QTcpSocket(this);
        _socket->connectToHost(QHostAddress("127.0.0.1"), 9999);

        connect(_socket, &QTcpSocket::readyRead, this, &NetGame::slotRecv);
        connect(_socket, &QTcpSocket::disconnected,[&](){
            mConnected=false;
        });
    }
}

void NetGame::slotRecv() {
    QByteArray ba = _socket->readAll();

    char cmd = ba[0];
    if (cmd == 1) {
        //初始化棋盘
        char data = ba[1];
        init(data == 1);
        mConnected=true;
    } else if (cmd == 2) {
        int row = ba[1];
        int col = ba[2];
        int id = ba[3];
        MyWidget::click(id, col, row);
    }
}

NetGame::~NetGame() {}

void NetGame::click(int id, int col, int row) {
    if(!mConnected) {

        if(id==-1||col<0||row<0||col>COL_COUNT||row>ROW_COUNT){
            qDebug() << "do nothing " ;
            return;
        }
        QMessageBox::information(this,"错误", "对方未连接");
        return;
    }
    //只允许点自己的棋子
    if (selectId == -1 && id != -1) {
        if (_s[id]._red != _bRedSide){

            qDebug() << "not your stone" ;
            return;
        }
    }

    MyWidget::click(id, col, row);
    qDebug() << "NetGame->MyWidget::click"<<id<<" "<< col <<" "<<row;

    if(_socket!=nullptr){
        char buf[4];
        buf[0] = 2;
        buf[1] = 9 - row;
        buf[2] = 8 - col;
        buf[3] = id;
        _socket->write(buf, 4);
    }
}
