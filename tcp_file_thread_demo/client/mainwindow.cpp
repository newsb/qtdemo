#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "filesend.h"

#include <QFile>
#include<QDateTime>
#include<QThread>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("客户端");
//getProxyCfg();



    qDebug()<<"MainWindow  currentThread:"<<QThread::currentThread();

    FileSend *fs=new FileSend();
    QThread *t=new QThread();
    fs->moveToThread(t);
    t->start();
    connect(this,&MainWindow::startConnect,fs,&FileSend::connectServer);
    connect(this,&MainWindow::startTestProxyConnection,fs,&FileSend::onTestProxyConnection);
    connect(this,&MainWindow::startSendFile,fs,&FileSend::sendfile);
    connect(fs,&FileSend::connectOK,this,[=](){
//        QMessageBox::information(this,"提示","连接服务器成功！");
        ui->btnSend->setEnabled(true);
    });
    connect(fs,&FileSend::connectBreak,this,[=](){
//        QMessageBox::information(this,"提示"," 服务器已断开！");
        ui->btnSend->setEnabled(false);
    });


    connect(fs,&FileSend::progressChanged,this,[=](int per){
        ui->progressBar->setValue(per);
    });
    connect(fs,&FileSend::sendOver,this,[=](){
       //发送完了
       t->quit();
       t->wait();
       t->deleteLater();
       fs->deleteLater();
       QMessageBox::information(this,"提示","发送完毕！");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnConnect_clicked()
{

    bool ok=false;
    quint16 port=ui->edtPort->text().toUInt(&ok);
    if(!ok) {
        qDebug()<<"  port err"; return;
    }
    QString ip=ui->edtIP->text();
    if(ip.isEmpty())
    {
        qDebug()<<"  ip err"; return;
    }

    bool isOn=ui->chbUseProxy->isChecked();
    QString proxyAddr=ui->edtPorxyIP->text();
    quint16 proxyPort=ui->edtProxyPort->text().toUInt();
    QString proxyUsr=ui->edtPorxyUsr->text();
    QString proxyPwd=ui->edtProxyPwd->text();
    int type=0;
    if(ui->cbbProxyType->currentIndex()==0){
        //http proxy
        type=1;
    }else if(ui->cbbProxyType->currentIndex()==1){
        //sock proxy
        type=2;
    }else if(ui->cbbProxyType->currentIndex()==2){
        //ie proxy
        //TODO:获取浏览器代理
        getProxyCfg();
//        type=3;
//         proxyAddr=ui->edtPorxyIP->text();
//         proxyPort=ui->edtProxyPort->text().toUInt();
//         proxyUsr=ui->edtPorxyUsr->text();
//         proxyPwd=ui->edtProxyPwd->text();
    }

    emit startConnect(ip,port,isOn,type,proxyAddr,proxyPort  ,proxyUsr ,proxyPwd);
}

#include <QFileDialog>

void MainWindow::on_btnSelect_clicked()
{
    QString s=QFileDialog::getOpenFileName(this,"文件选择","",tr("{ALL File(*.*)"));
    if(!s.isEmpty()){
        ui->edtPath->setText(s);
    }

}

void MainWindow::on_btnSend_clicked()
{
    QString path=ui->edtPath->text();

    if(path.isEmpty()){
        qDebug()<<" select file null";
        return;
    }
    emit startSendFile(path);

}



void MainWindow::on_chbUseProxy_stateChanged(int state)
{

    qDebug()<<"stateChanged:"<<state;
    bool b=state==Qt::Checked&&ui->cbbProxyType->currentIndex()!=2;
    ui->cbbProxyType->setEnabled(b);
    ui->edtPorxyIP->setEnabled(b);
    ui->edtProxyPort->setEnabled(b);
    ui->btnTest->setEnabled(b);
    ui->lblAddr->setEnabled(b);
    ui->lblPort->setEnabled(b);
    ui->lblUsr->setEnabled(b);
    ui->lbpwd->setEnabled(b);
    ui->edtPorxyUsr->setEnabled(b);
    ui->edtProxyPwd->setEnabled(b);

}


void MainWindow::on_btnTest_clicked()
{
    QString proxyAddr=ui->edtPorxyIP->text();
    quint16 proxyPort=ui->edtProxyPort->text().toUInt();
    QString proxyUsr=ui->edtPorxyUsr->text();
    QString proxyPwd=ui->edtProxyPwd->text();
    emit startTestProxyConnection(proxyAddr,proxyPort,proxyUsr,proxyPwd);
}
#include <QFile>
#include <QLibrary>
//#include "dll.h"             //引入头文件
typedef char * (*Fun)(); //定义函数指针，以备调用
QString MainWindow::getProxyCfg()
{
    QString fn="mylib.dll";
    QFile f(fn);
    if (!f.exists()){
        QMessageBox::information(NULL,"OK","file :"+fn+" not exitsed " );
    }
    QLibrary mylib(fn);   //声明所用到的dll文件

    char* result;
    if (mylib.load())              //判断是否正确加载
    {
        QMessageBox::information(NULL,"OK","DLL Trade_exe.dll load is OK!");
        Fun open=(Fun)mylib.resolve("testfun2");    //援引 add() 函数
        if (open)            //是否成功连接上 add() 函数
        {
            QMessageBox::information(NULL,"OK","Link to Function is OK!");
            result= open();      //这里函数指针调用dll中的 add() 函数
            qDebug()<<result;
        }
        else
            QMessageBox::information(NULL,"NO","Linke to Function is not OK!!!!");
    }
    else{
        QMessageBox::information(NULL,"NO","DLL is not loaded："+mylib.errorString());
    }

//    bool fAutoProxy=FALSE;
//    WINHTTP_CURRENT_USER_IE_PROXY_CONFIG ieProxyConfig;
//    if( WinHttpGetIEProxyConfigForCurrentUser( &ieProxyConfig ) ){
//        if( ieProxyConfig.fAutoDetect )
//        {
//            fAutoProxy = TRUE;
//        }

//        if( ieProxyConfig.lpszAutoConfigUrl != NULL )
//        {
//            fAutoProxy = TRUE;
//            autoProxyOptions.lpszAutoConfigUrl = ieProxyConfig.lpszAutoConfigUrl;
//        }
//    }
//    else
//    {
//        // use autoproxy
//        fAutoProxy = TRUE;
//    }

//    if( fAutoProxy )
//    {
//        if ( autoProxyOptions.lpszAutoConfigUrl != NULL )
//        {
//            autoProxyOptions.dwFlags = WINHTTP_AUTOPROXY_CONFIG_URL;
//        }
//        else
//        {
//            autoProxyOptions.dwFlags = WINHTTP_AUTOPROXY_AUTO_DETECT;
//            autoProxyOptions.dwAutoDetectFlags = WINHTTP_AUTO_DETECT_TYPE_DHCP | WINHTTP_AUTO_DETECT_TYPE_DNS_A;
//        }

//        // basic flags you almost always want
//        autoProxyOptions.fAutoLogonIfChallenged = TRUE;

//        // here we reset fAutoProxy in case an auto-proxy isn't actually
//        // configured for this url
//        fAutoProxy = WinHttpGetProxyForUrl( hiOpen, pwszUrl, &autoProxyOptions, &autoProxyInfo );
//    }

//    if ( fAutoProxy )
//    {
//        // set proxy options for libcurl based on autoProxyInfo
//    }
//    else
//    {
//        if( ieProxyConfig.lpszProxy != NULL )
//        {
//            // IE has an explicit proxy. set proxy options for libcurl here
//            // based on ieProxyConfig
//            //
//            // note that sometimes IE gives just a single or double colon
//            // for proxy or bypass list, which means "no proxy"
//        }
//        else
//        {
//            // there is no auto proxy and no manually configured proxy
//        }
//    }
    return "";
}

void MainWindow::on_cbbProxyType_currentIndexChanged(int index)
{
    bool b=ui->chbUseProxy->isChecked()&&2!=index;
    ui->edtPorxyIP->setEnabled(b);
    ui->edtProxyPort->setEnabled(b);
    ui->lblAddr->setEnabled(b);
    ui->lblPort->setEnabled(b);
    ui->lblUsr->setEnabled(b);
    ui->lbpwd->setEnabled(b);
    ui->edtPorxyUsr->setEnabled(b);
    ui->edtProxyPwd->setEnabled(b);
}


































