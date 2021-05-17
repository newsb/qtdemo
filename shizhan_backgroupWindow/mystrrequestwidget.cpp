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
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QStringList>
#include <QDebug>

void MyStrRequestWidget::on_pushButton_2_clicked()
{
    /////////////////////////////////////
    /// \brief JSON STRING -> QJsonDocument -> JSON OBJECT or ARRAY ? -> QJsonValue
    /////////////////////////////////////
    QString json("{\"name\":\"scorpio\", \"year\":2016, \"array\":[30, \"hello\", true]}");
    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(json.toLatin1(), &jsonerror);
    if (doc.isNull() || jsonerror.error != QJsonParseError::NoError)
    {
        qDebug()<< jsonerror.error << ":"<< jsonerror.errorString();
        return ;
    }
    if(doc.isObject())
    {
        QJsonObject object = doc.object();
        QStringList list = object.keys();
        qDebug() << list;//("array", "name", "year")

        QJsonObject::iterator it = object.begin();
        while(it != object.end())
        {
            switch(it.value().type()){
                case QJsonValue::String:
                {
                    qDebug() << "Type is string";
                    QJsonArray sub = it.value().toArray();
                    qDebug() << it.key() << "=" << it.value().toString();
                    //"array" = QJsonArray([30,"hello",true])  、 "name" = "scorpio"
                    break;
                }
                case QJsonValue::Array:
                {
                    qDebug() << "Type is Array";
                    qDebug() << it.key() << "=" << it.value().toArray();
                    QJsonArray sub = it.value().toArray();
                    qDebug() << "index 1:" << sub.at(0).toDouble();//index 1: 30
                    qDebug() << "index 2:" << sub.at(1).toString();//index 2: "hello"
                    qDebug() << "index 3:" << sub.at(2).toBool();//index 3: true
                    break;
                }
                case QJsonValue::Bool:
                {
                    qDebug() << "Type is Bool";
                    qDebug() << it.key() << "=" << it.value().toBool();
                    break;
                }
                case QJsonValue::Double:
                {
                    qDebug() << "Type is Double";
                    qDebug() << it.key() << "=" << it.value().toDouble(); //"year" = 2016
                    break;
                }
                case QJsonValue::Object:
                {
                    qDebug() << "Type is Object";
                    qDebug() << it.key() << "=" << it.value().toObject();
                    break;
                }
                case QJsonValue::Null:
                {
                    qDebug() << "Type is Null";
                    qDebug() << it.key() << "= NULL" ;
                    break;
                }
                case QJsonValue::Undefined:
                {
                    qDebug() << "Type is Undefined";
                    break;
                }
            }
            it++;
        }
    }

}

void MyStrRequestWidget::on_pushButton_3_clicked()
{
    QString s="{\"code\":200,\"data\":{\"ext\":{},\"size\":2,\"items\":[{\"ext\":null,\"resourceId\":\"\",\"mediaAssetInfo\":null,\"productId\":\"QAxWidget\",\"reportData\":{\"eventClick\":true,\"data\":{\"mod\":\"popu_895\",\"dist_request_id\":\"1621238777842_13933\",\"index\":\"1\",\"strategy\":\"alirecmd\"},\"urlParams\":{\"utm_medium\":\"distribute.pc_search_hot_word.none-task-hot_word-alirecmd-1.nonecase\",\"depth_1-utm_source\":\"distribute.pc_search_hot_word.none-task-hot_word-alirecmd-1.nonecase\"},\"eventView\":true},\"recommendType\":\"ali\",\"index\":1,\"style\":null,\"strategyId\":\"alirecmd\",\"productType\":\"hot_word\"},{\"ext\":null,\"resourceId\":\"\",\"mediaAssetInfo\":null,\"productId\":\"插件\",\"reportData\":{\"eventClick\":true,\"data\":{\"mod\":\"popu_895\",\"dist_request_id\":\"1621238777842_13933\",\"index\":\"2\",\"strategy\":\"alirecmd\"},\"urlParams\":{\"utm_medium\":\"distribute.pc_search_hot_word.none-task-hot_word-alirecmd-2.nonecase\",\"depth_1-utm_source\":\"distribute.pc_search_hot_word.none-task-hot_word-alirecmd-2.nonecase\"},\"eventView\":true},\"recommendType\":\"ali\",\"index\":2,\"style\":null,\"strategyId\":\"alirecmd\",\"productType\":\"hot_word\"}]},\"message\":\"success\"}";
    QString json(s);//ui->textEdit->toPlainText());
    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8(), &jsonerror);
    if (doc.isNull() || jsonerror.error != QJsonParseError::NoError)
    {
        qDebug()<< jsonerror.error << ":"<< jsonerror.errorString();
        return ;
    }

    if(doc.isObject())
    {
        QJsonValue val=doc["code"];
        int  code=val.toInt();
        qDebug() << "code="<<code;
        QJsonValue data=doc["data"];
//        if(!val.isObject()){
//            return;
//        }
        int size=data["size"].toInt();
        qDebug() << "size="<<size;

        QJsonValue items=data["items"];
        if(QJsonValue::Array==items.type()){
            QJsonArray itemArr=items.toArray();
            if(itemArr.count()>0){
                for(int i=0;i<itemArr.count();i++){
                    QJsonValue obj= itemArr.at(i);
                    QString productId=obj["productId"].toString();
                    qDebug() <<i<< " productId="<<productId;
                }
            }
        }
    }
}
