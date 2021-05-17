#include "httptestwidget.h"
#include<QVBoxLayout>

HttpTestWidget::HttpTestWidget(QWidget *parent) : QWidget(parent)
{
    QLineEdit * le=new QLineEdit(this);
    le->setGeometry(10,10,this->width(),50);
    le->clear();
    le->setText("http://img.mp.itc.cn/upload/20170302/6ffa8469d1c34a90918cdd71014841c0_th.jpg");

    QPushButton *btn=new QPushButton(this);
    btn->setGeometry(10,110,this->width(),50);
    btn->setText("get image");
 QLabel *imageLabel = new QLabel;

    QLabel *sizeLabel = new QLabel;
//    sizeLabel->move(11, btn->y()-24 );

//    QImage image(":/res/1.jpg");
    QScrollArea *scrollArea = new QScrollArea(this);

    connect(btn,&QPushButton::clicked,[=](){

        QImage image= this->downloadImage(le->text());
        mPix=QPixmap::fromImage(image);
        sizeLabel->setText(QString("%1 X %2").arg(mPix.width()).arg(mPix.height()));

scrollArea->setBackgroundRole(QPalette::Dark);
int top1=(btn->y()+btn->height()+11);
scrollArea->setGeometry(0,top1,this->width(),height()-top1);
imageLabel->setGeometry(0,0,mPix.width()+11,mPix.height()+11);
scrollArea->setWidget(imageLabel);
        imageLabel->setPixmap(mPix);
        scrollArea->show();


//
//        update();
    });

//    this->showMaximized();
    QVBoxLayout *box=new QVBoxLayout(this);
    box->addWidget(le);
    box->addWidget(btn);
    box->addWidget(sizeLabel);
    box->addWidget(scrollArea);
    this->setLayout(box);


    ////////////////////////

    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();
}

// #include <QPainter>
//void HttpTestWidget::paintEvent(QPaintEvent *event)
//{
//    QPainter p(this);
//    p.drawPixmap(0,0,mPix);
//    QWidget::paintEvent(event);
//}

#include <QEventLoop>

QImage HttpTestWidget::downloadImage(const QString &url)
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

    QImage image=QImage::fromData(data);
    return image;
}

void HttpTestWidget::doHttpErr(QNetworkReply::NetworkError code){
    qDebug()<<"request err:"<<code  ;
}
