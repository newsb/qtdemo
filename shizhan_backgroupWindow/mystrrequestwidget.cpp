#include "mystrrequestwidget.h"
#include "ui_mystrrequestwidget.h"
#include <QDebug>

MyStrRequestWidget::MyStrRequestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyStrRequestWidget)
{
    ui->setupUi(this);

    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();

}

MyStrRequestWidget::~MyStrRequestWidget()
{
    delete ui;
}

void MyStrRequestWidget::on_pushButton_clicked()
{

    ui->textEdit->setText("");
    QString str= this->doRequest(ui->lineEdit->text());

    qDebug()<<"str ="<<str;

    ui->textEdit->setPlainText(str);
//    ui->textEdit->setText(str);

}

#include <QEventLoop>

QString MyStrRequestWidget::doRequest(const QString &url)
{
    QNetworkProxy proxy(QNetworkProxy::HttpProxy,"172.16.0.1",3128);
    QNetworkAccessManager mgr;
    mgr.setProxy(proxy);

    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QNetworkReply *reply=mgr.get(request);



//    void (QNetworkReply::*mySignal)(QNetworkReply::NetworkError)=&QNetworkReply::error;
//     connect(reply,mySignal,this,&HttpTestWidget::doHttpErr);

//    connect(reply,QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),this,&HttpTestWidget::doHttpErr);

        connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            [=](QNetworkReply::NetworkError code){

            qDebug()<<"request err:"<<code <<";errstring:"<<reply->errorString();
        });

        connect(reply,&QNetworkReply::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal){

            qDebug()<<"downloadProgress bytesReceived:"<<bytesReceived <<";bytesTotal:"<< bytesTotal;
        });

qDebug()<<"request...";
    //用事件循环卡住，等待请求request完成
    QEventLoop loop;
    connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
qDebug()<<"request ok ,reply="<<reply;

    QByteArray data =reply->readAll();
    QString s =data;
    return s;
}
