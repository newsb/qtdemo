#include "MyWidget.h"
#include "SingleGame.h"
#include "netgame.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //    MyWidget w; // 2ren 版 ok

    //    SingleGame w; //单机+机器人  ok

    //    网络 + 2人
    bool bServer = false;
    QMessageBox::StandardButton ret = QMessageBox::question(nullptr, "server or client?", "作为服务器启动？");
    if (ret == QMessageBox::Yes) {
        bServer = true;
    }
    NetGame w(bServer);

    w.show();
    return a.exec();
}
