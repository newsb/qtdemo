#ifndef NETGAME_H
#define NETGAME_H
#include <MyWidget.h>
#include <QTcpServer>
#include <QTcpSocket>
class NetGame : public MyWidget {
    Q_OBJECT
  public:
    NetGame(bool isServer);
    ~NetGame();

    QTcpServer *_server;
    QTcpSocket *_socket;

    // MyWidget interface
  protected:
    virtual void click(int id, int col, int row) override;
  public slots:
    void slotRecv();
};

#endif // NETGAME_H
