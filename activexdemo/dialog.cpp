#include "dialog.h"
#include "ui_dialog.h"

#include <QAxObject>
#include <QFile>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);


}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QAxObject obj("SAPI.SpVoice");
    //生产文档
//    QString doc=obj.generateDocumentation();
//    QFile f("SAPI.SpVoice.html");
//    f.open(QIODevice::WriteOnly);
//    f.write(doc.toUtf8());
//    f.close();


//    QVariantList params = ...
    int resultCode = obj.dynamicCall("Speak(QString, SpeechVoiceSpeakFlags)", ui->plainTextEdit->toPlainText()).toInt();
    ui->plainTextEdit->appendPlainText("play finished:"+QString::number(resultCode));
}

#include "exceloperator.h"

void Dialog::on_pushButton_2_clicked()
{
    ExcelOperator eo(this);
    bool ret=eo.open("C:\\Users\\EDZ\\Desktop\\aaa.xlsx");
    if(!ret)
        return;
    qDebug()<<"getSheetsCount:"<<eo.getSheetsCount();

    eo.addSheet("hmm");
    eo.addSheet("sb");
    eo.delSheet("sb");

    QAxObject* sheet=eo.getSheet("hmm");
    qDebug()<< "getRowsCount:"<< eo.getRowsCount(sheet);

    QString cell1010=eo.getCell(sheet,10,10);
    qDebug()<< "cell1010:"<< cell1010;

    eo.setCell(sheet,10,10,"usb25000000chshi");
    qDebug()<< "cell1010:"<< eo.getCell(sheet,10,10);
    eo.close();



    //    QAxObject obj("KET.Application");
//    QVariant v=obj.property("Workbooks") ;
//    IDispatch* val = object->property("Workbooks").toIDispatch*();
//    Workbooks * =v.to
//    //生产文档
//    QString doc=obj.generateDocumentation();

//    QFile f("KET.Application.html");
//    f.open(QIODevice::WriteOnly);
//    f.write(doc.toUtf8());
//    f.close();
}
