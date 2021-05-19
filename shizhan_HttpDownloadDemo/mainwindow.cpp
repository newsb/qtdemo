#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_pushButton_clicked()
{
    QStringList urls;
    urls <<"http://img.netbian.com/file/2020/0904/de2f77ed1090735b441ba5e4c2b460ca.jpg"
        <<"http://img.netbian.com/file/2020/0904/9b933abf1608906132ef3d924910ae9e.jpg"
        <<"http://img.netbian.com/file/2021/0518/093f6ed69f963d83f696500dbf88845b.jpg"
        <<"http://img.netbian.com/file/2020/1217/3a4ccdf21539f42d4e1aca5de6091ffd.jpg"
        <<"http://img.netbian.com/file/2021/0418/1faf056bc407f455b9031b5375025b8a.jpg"
        <<"http://img.netbian.com/file/2020/0904/7cab180eca805cce596b6870cb4e1379.jpg"
        <<"http://img.netbian.com/file/2020/0904/c150c8a4fdf8762f51093f636c7de785.jpg"
        <<"http://img.netbian.com/file/2020/0904/5318ab688977d41445fabb118c0d039e.jpg"
        <<"http://img.netbian.com/file/2020/0904/919e45e8a57d4d7d3a783eeb110a7285.jpg"
        <<"http://img.netbian.com/file/2020/0904/dbb00a5646309df5fad6efda1079e756.jpg"
        <<"http://img.netbian.com/file/2021/0502/5dcb9bd99c4113b2fb283ef52d16a8b7.jpg"
        <<"http://img.netbian.com/file/2020/0904/8bb658e4c5aaa124e3f37069c047735c.jpg"
        <<"http://img.netbian.com/file/2019/0824/small4a68818befe4ec269bf52b6f6f6ccae61566660671.jpg"
        <<"http://img.netbian.com/file/newc/c6d42913c0440bdb5ffeec9c90236d66.jpg"
        <<"http://img.netbian.com/file/2021/0510/small6e1e58e4c74f986aaabb870ce919e99f1620618148.jpg"
        <<"http://img.netbian.com/file/newc/d36a375c5399ff3a1982ce867a328e34.jpg"
        <<"http://img.netbian.com/file/2021/0418/small72c623a07d9b7bebb542fab509393ed91618757624.jpg"
        <<"http://img.netbian.com/file/newc/c092812c434904a5b29fc3454485aaf1.jpg"
        <<"http://img.netbian.com/file/2019/0905/smalla5c693ca2a2d8746583d16353f45c0b31567645256.jpg"
        <<"http://img.netbian.com/file/2019/0306/small91ce17dda2b11e57d08e25287cdb556f1551837909.jpg"
        <<"http://img.netbian.com/file/newc/ab9a62517bbe072eeaff79341cb09506.jpg"
        <<"http://img.netbian.com/file/newc/fc3e199e91cf51efff9ea71d18943bed.jpg"
        <<"http://img.netbian.com/file/2020/0901/small1a374f1629daeb4dea9782d09b47d8231598950853.jpg"
        <<"http://img.netbian.com/file/2019/0401/small91779be3cecd3c8688013dbe2ce9a00a1554126462.jpg"
        <<"http://img.netbian.com/file/2020/0909/193023b3f65c0f4f9831a7c475b01485.jpg"
        <<"http://img.netbian.com/file/2021/0519/small2e6abd6e87d61a15dc4472e98a0f59ee1621354231.jpg"
        <<"http://img.netbian.com/file/2021/0519/small4a72b556cf1deda73ac0cea68d6caa701621354136.jpg"
        <<"http://img.netbian.com/file/2021/0312/021b2748efe5bcdebfb828083b6747f4.jpg"
        <<"http://img.netbian.com/file/2021/0519/smallf170a17ad1ee721a3489012b197186301621353917.jpg"
        <<"http://img.netbian.com/file/2021/0519/small1e932376b482fb517f5cc24047d0111e1621353620.jpg"
        <<"http://img.netbian.com/file/2021/0517/small40d63659e3fa6c847bc0e99e80f96b2e1621258686.jpg"
        <<"http://img.netbian.com/file/2021/0517/smallca943fe95313f5d4d53572fc083cbada1621258612.jpg"
        <<"http://img.netbian.com/file/2021/0517/small1adead5beabeda8423bce4ed7ade36a91621258439.jpg"
        <<"http://img.netbian.com/file/2021/0517/small6bb76e6c08c22bd778b4382255574ba01621258364.jpg"
        <<"http://img.netbian.com/file/2021/0517/smallbe11255413d82e8a7e357a96ae23fc6d1621258165.jpg"
        <<"http://img.netbian.com/file/2021/0516/small3aeb174d78be439c80f528e2a680528a1621179217.jpg"
        <<"http://img.netbian.com/file/2021/0516/small21ebdef585ced49e8d5a80f85788e2dc1621179095.jpg"
        <<"http://img.netbian.com/file/2021/0516/smalla6b3ec4730bcd6ead2502ff2ca7b7f081621178601.jpg"
        <<"http://img.netbian.com/file/2021/0514/small8b9bdde62a7b946b7dcc17fc345af27b1621007164.jpg"
        <<"http://img.netbian.com/file/2021/0514/small7f2856a247d613212f58c302b23d07cf1621006407.jpg"
        <<"http://img.netbian.com/file/2021/0513/smallf6e2957220ae703d31c7ed9d2d5d82851620921508.jpg"
        <<"http://img.netbian.com/file/2021/0513/smallb6c0be95f8a48c05133c575939b5da6a1620921319.jpg"
        <<"http://img.netbian.com/file/2021/0512/smallf399ffe785695e4c115fe20b34519c421620831512.jpg"
        <<"http://img.netbian.com/file/2021/0512/small43e68dd7aeebc416f3d4780a844fee971620831392.jpg"
        <<"http://img.netbian.com/file/2021/0511/small73637d4f1ee83fd5e25534d47354b1f51620745003.jpg"

       <<"http://img.netbian.com/file/2021/0519/small2e6abd6e87d61a15dc4472e98a0f59ee1621354231.jpg"
       <<"http://img.netbian.com/file/2021/0519/small4a72b556cf1deda73ac0cea68d6caa701621354136.jpg"
       <<"http://img.netbian.com/file/2021/0519/smallf170a17ad1ee721a3489012b197186301621353917.jpg"
       <<"http://img.netbian.com/file/2021/0519/small1e932376b482fb517f5cc24047d0111e1621353620.jpg"
       <<"http://img.netbian.com/file/2021/0517/small40d63659e3fa6c847bc0e99e80f96b2e1621258686.jpg"
       <<"http://img.netbian.com/file/2021/0517/smallca943fe95313f5d4d53572fc083cbada1621258612.jpg"
       <<"http://img.netbian.com/file/2021/0517/small1adead5beabeda8423bce4ed7ade36a91621258439.jpg"
       <<"http://img.netbian.com/file/2021/0517/small6bb76e6c08c22bd778b4382255574ba01621258364.jpg"
       <<"http://img.netbian.com/file/2021/0517/smallbe11255413d82e8a7e357a96ae23fc6d1621258165.jpg"
       <<"http://img.netbian.com/file/2021/0516/small3aeb174d78be439c80f528e2a680528a1621179217.jpg"
       <<"http://img.netbian.com/file/2021/0516/small21ebdef585ced49e8d5a80f85788e2dc1621179095.jpg"
       <<"http://img.netbian.com/file/2021/0516/smalla6b3ec4730bcd6ead2502ff2ca7b7f081621178601.jpg"
       <<"http://img.netbian.com/file/2021/0514/small8b9bdde62a7b946b7dcc17fc345af27b1621007164.jpg"
       <<"http://img.netbian.com/file/2021/0514/small7f2856a247d613212f58c302b23d07cf1621006407.jpg"
       <<"http://img.netbian.com/file/2021/0513/smallf6e2957220ae703d31c7ed9d2d5d82851620921508.jpg"
       <<"http://img.netbian.com/file/2021/0513/smallb6c0be95f8a48c05133c575939b5da6a1620921319.jpg"
       <<"http://img.netbian.com/file/2021/0512/smallf399ffe785695e4c115fe20b34519c421620831512.jpg"
       <<"http://img.netbian.com/file/2021/0512/small43e68dd7aeebc416f3d4780a844fee971620831392.jpg"
       <<"http://img.netbian.com/file/2021/0511/small73637d4f1ee83fd5e25534d47354b1f51620745003.jpg"
           ;
    foreach(QString url,urls){
        QNetworkAccessManager *mgr=new QNetworkAccessManager();
        QNetworkProxy proxy(QNetworkProxy::HttpProxy,"172.16.0.1",3128);
        mgr->setProxy(proxy);

        QNetworkRequest request((QUrl(url)));
//        request.setUrl(QUrl(url));
        QNetworkReply *reply=mgr->get(request);
        connect(reply,&QNetworkReply::finished,this,&MainWindow::onFinished);
    }
}

#include <QFileInfo>

void MainWindow::onFinished()
{
    QObject *obj =this->sender();//发送信号的对象
//    QNetworkReply *reply = (QNetworkReply *)obj;//普通的强制转换
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(obj);//转换失败返回NULL,父子类转换用dmyic_cast。。。
    if(reply==NULL) return;

    //释放mgr
    QNetworkAccessManager *mgr=reply->manager();
    mgr->deleteLater();

    //从url获取文件名
    QFileInfo info(reply->url().toString());
    QString fn=info.fileName();

    QByteArray data= reply->readAll();

    QImage image;
    image.loadFromData(data);
    image.save(fn);
}
