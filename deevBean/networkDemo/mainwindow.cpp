#include "mainwindow.h"
#include <QDebug>
#include <QEventLoop>
#include <QHBoxLayout>
#include <QNetworkReply>
class MainWindow::Private
{
public:
    Private()
    {
        netWorker = NetWorker::instance();
    }
    //MainWindow::Private提供了一个fetchWeather()函数。
    //由于NetWorker提供的函数都是相当底层的，为了提供业务级别的处理，我们将这样的函数封装在MainWindow::Private中。
    void fetchWeather(const QString &cityName) const
    {
        QNetworkReply *reply =netWorker->get(QString("http://www.baidu.com/"));
    }

    void fetchWeather2(const QString &cityName) const
    {
        /*
我们在函数中创建了一个QEventLoop实例，将其quit()与NetWorker::finished()信号连接起来。
当NetWorker::finished()信号发出时，QEventLoop::quit()就会被调用。
在NetWorker::get()执行之后，调用QEventLoop::exec()函数开始事件循环。此时界面就是被阻塞。
        */
        QEventLoop eventLoop;
        connect(netWorker, &NetWorker::finished, &eventLoop, &QEventLoop::quit);
        QNetworkReply *reply =netWorker->get(QString("http://www.baidu.com"));
//        replyMap.insert(reply, FetchWeatherInfo);
        eventLoop.exec();
    }

    //将MainWindow所需要的NetWorker作为MainWindow::Private的一个成员变量。
    NetWorker *netWorker;
};

MainWindow::MainWindow(QWidget *parent) :
      QMainWindow(parent),
      d(new MainWindow::Private)
{
    connect(d->netWorker, &NetWorker::finished, [=] (QNetworkReply *reply) {
        qDebug() << reply->readAll();
//        QJsonParseError error;
//        QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &error);
//        if (error.error == QJsonParseError::NoError) {
//        } else {
//            QMessageBox::critical(this, tr("Error"), error.errorString());
//        }

        //函数的最后一行，reply->deleteLater();。当网络请求结束时，delete 服务器返回的QNetworkReply对象是用户的责任。
        //用户需要选择一个恰当的时机进行 delete 操作。但是，我们不能直接在finiahed()信号对应的槽函数中调用delete运算符。
        //相反，我们需要使用deleteLater()函数，正如前面代码中显示的那样。第二个槽函数则相对简单，仅仅是重新获取新的数据。
//        reply->deleteLater();
    });

    refreshButton=new QPushButton(this);
    refreshButton->setText("GET HTTP DATA");
    refreshButton2=new QPushButton(this);
    refreshButton2->setText("GET HTTP SYNC");

    connect(refreshButton2, &QPushButton::clicked, [=] () {
        d->fetchWeather2("");
    });
    connect(refreshButton, &QPushButton::clicked, [=] () {
        d->fetchWeather("");
    });

    QHBoxLayout  *box = new QHBoxLayout;
    box->addWidget(refreshButton);
    box->addWidget(refreshButton2);
//!!! QMainWindow 必须拥有一个 a central widget，即使只是占位
    QWidget * centerWindow = new QWidget ;
    this->setCentralWidget(centerWindow);
    centerWindow->setLayout(box);
}
