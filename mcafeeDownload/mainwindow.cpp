#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

const QString LIST_URL="http://download.nai.com/products/licensed/superdat/english/intel/";
const QString TEST_URL="http://download.nai.com/products/licensed/superdat/english/intel/10080xdat.exe";

void MainWindow::startListFile()
{
    this->log("1、list file...");
    QNetworkAccessManager *mgr=new QNetworkAccessManager();
    QNetworkProxy proxy(QNetworkProxy::HttpProxy,"172.16.0.11",3128);
    mgr->setProxy(proxy);
    QString url=LIST_URL;
    QNetworkRequest request((QUrl(url)));
//        request.setUrl(QUrl(url));

    QEventLoop eventLoop;
    QNetworkReply *reply2=mgr->get(request);
    connect(reply2,&QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    connect(reply2,&QNetworkReply::finished,this,&MainWindow::onlistFileFinished);
    connect(reply2, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this,&MainWindow::onErr);
    eventLoop.exec();
}

void MainWindow::onlistFileFinished(){

    QObject *obj =this->sender();//发送信号的对象
//    QNetworkReply *reply = (QNetworkReply *)obj;//普通的强制转换
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(obj);//转换失败返回NULL,父子类转换用dmyic_cast。。。

    if(reply==NULL) {
        ui->edtLog->append("reply is null");
        return;
    }
    QString body=reply->readAll();

    log("list file end:");

    //TODO:parser boy to get newest filename
     (body);

    startGetHeaderSize(TEST_URL);
}

void MainWindow::startGetHeaderSize(const QString url)
{
    QNetworkAccessManager *mgr=new QNetworkAccessManager();
    QNetworkProxy proxy(QNetworkProxy::HttpProxy,"172.16.0.11",3128);
    mgr->setProxy(proxy);

    QEventLoop eventLoop;
    QNetworkRequest request((QUrl(url)));
    QNetworkReply *reply2=mgr->head(request);
    connect(reply2,&QNetworkReply::finished,&eventLoop,&QEventLoop::quit );
    connect(reply2,&QNetworkReply::finished,this,&MainWindow::onHeaderFinished);
    connect(reply2, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this,&MainWindow::onErr);
    eventLoop.exec();
}

void MainWindow::onHeaderFinished(){

    QObject *obj =this->sender();//发送信号的对象
//    QNetworkReply *reply = (QNetworkReply *)obj;//普通的强制转换
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(obj);//转换失败返回NULL,父子类转换用dmyic_cast。。。

    if(reply==NULL) {
        ui->edtLog->append("reply is null");
        return;
    }
    QVariant var=reply->header(QNetworkRequest::ContentLengthHeader);

    QString iSize=var.toString();

    ui->lblSize->setText(iSize);


    startDownloadFile(TEST_URL);
}


void MainWindow::startDownloadFile(const QString url)
{
    QNetworkAccessManager *mgr=new QNetworkAccessManager();
    QNetworkProxy proxy(QNetworkProxy::HttpProxy,"172.16.0.11",3128);
    mgr->setProxy(proxy);
    QEventLoop event;
    QNetworkRequest request((QUrl(url)));
    QNetworkReply *reply=mgr->get(request);
    connect(reply,&QNetworkReply::finished,&event,&QEventLoop::quit);
    connect(reply,&QNetworkReply::finished,this,&MainWindow::onFinished);

    connect(reply,&QNetworkReply::downloadProgress,this,&MainWindow::onDownloadProgressChange);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this,&MainWindow::onErr);
    event.exec();
}

void MainWindow::onDownloadProgressChange(qint64 bytesReceived, qint64 bytesTotal)
{
    int per=bytesReceived*100/bytesTotal;
    ui->progressBar->setValue(per);
    double dRec=bytesReceived/(1024.0*1024);
    double dTotal=bytesTotal/(1024.0*1024);
    QString s=QString::number(dRec,'f',2)+"M / "+QString::number(dTotal,'f',2)+"M/";
    ui->lblSize->setText(s);
}

void MainWindow::log(const QString s)
{
    ui->edtLog->append(s);
}

void MainWindow::onFinished(){

    ui->progressBar->setValue(100);
}
void MainWindow::on_btnDownload_clicked()
{
    startListFile();

    /*
    startGetHeaderSize(TEST_URL);
    startDownloadFile(TEST_URL);
*/
}

void MainWindow::onErr(QNetworkReply::NetworkError code){
     QObject *obj =this->sender();
     QNetworkReply *reply = qobject_cast<QNetworkReply *>(obj);//
     ui->edtLog->append(&"reply err: code="[code]);
     if(reply==NULL) {
         ui->edtLog->append("reply is null");
         return;
     }
     ui->lblTip->setText(reply->errorString());
     ui->edtLog->append("reply errString:"+reply->errorString());
}


void MainWindow::on_btnPause_clicked()
{
}
