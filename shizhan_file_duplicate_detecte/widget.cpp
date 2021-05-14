#include "widget.h"
#include "ui_widget.h"

#include <QSplitter>
#include <QGraphicsDropShadowEffect>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,myThread(new QThread())
    ,mymd5(new MyMd5())
{
    ui->setupUi(this);

    setWindowTitle("无边框窗口、可拖动窗体、窗体圆角阴影、文件重复检查");
    ui->lblCaption->setText(windowTitle());

    // Qt::FramelessWindowHint 无边框
    setWindowFlags(Qt::FramelessWindowHint);

    //阴影边框效果类型，
    QGraphicsDropShadowEffect * shadow=new QGraphicsDropShadowEffect();

    shadow->setBlurRadius(15);
    shadow->setColor(Qt::blue);
    shadow->setOffset(0);

    ui->shadowWidget->setGraphicsEffect(shadow);
//    this->setGraphicsEffect(shadow);

    //设置父窗口透明
    this->setAttribute(Qt::WA_TranslucentBackground);


    this->layout()->setMargin(9);


    myThread->start();
    mymd5->moveToThread(myThread);

    connect(this,&Widget::startCalcMd5,mymd5,&MyMd5::onStartCalcMd5);
    connect(mymd5,&MyMd5::progress_changed,this,&Widget::onMyProgressChanged);
    connect(mymd5,&MyMd5::calcMd5Finished,this,&Widget::onCalcMd5Finished);


    QSplitter *splitterMain = new QSplitter(Qt::Horizontal, ui->widget);
    splitterMain->setStyleSheet("QSplitter{border: 0px;}");
    ui->horizontalLayout_3->addWidget(splitterMain);
    splitterMain->addWidget(ui->listWidget);
    splitterMain->addWidget(ui->listWidget_2);
    splitterMain->setStretchFactor(1,1);
    splitterMain->setWindowTitle(QObject::tr("分割窗口"));
    splitterMain->show();

}

Widget::~Widget()
{
    myThread->exit();
    myThread->wait();

    delete ui;
}



void Widget::onMyProgressChanged(int progress)
{
    ui->progressBar->setValue(progress);
}

#include <QMouseEvent>

void Widget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    QPoint y=event->globalPos();//鼠标相对于桌面左上角位置，全局坐标
    QPoint x=this->geometry().topLeft();//窗口左上角相对于桌面左上角位置
    z=y-x;//向量运算，拖动时z是定值，

}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    z=QPoint();//清空变量z
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if(z==QPoint()){
        return;
    }
    QPoint y=event->globalPos();//鼠标相对于桌面左上角位置，全局坐标
    QPoint x=y-z;//鼠标相对于桌面左上角位置，全局坐标

    this->move(x);
}


void Widget::on_btnClose_clicked()
{
    this->close();
}

void Widget::on_btnMax_clicked()
{
    if (this->isMaximized()){
        this->layout()->setMargin(9);
        this->showNormal();
    }else{
        this->layout()->setMargin(0);
        this->showMaximized();
    }
}

void Widget::on_btnMin_clicked()
{
    this->showMinimized();
}

#include <QFileDialog>
#include <QDebug>

void Widget::on_pushButton_clicked()
{
    mDuplication.clear();

    QString path=QFileDialog::getExistingDirectory(this,"select a dir",".");
    if(path.isEmpty()) return ;

    qDebug()<<"path："<<path;
    ui->lineEdit->setText(path);

    //遍历目录下的所有文件和子文件
    QStringList list=getFiles(path);
    ui->progressBar->setMaximum(list.count());
    ui->progressBar->setValue(0);

    emit startCalcMd5(list);


//    for(int i=0;i<list.count();i++){
//        QString filename=list.at(i);
//        QByteArray md5=getFileMd5(filename);

//        mDuplication[md5].append(filename);
//        ui->progressBar->setValue(i+1);
//    }

//    //显示结果
//    ui->listWidget->clear();
//    for (QHash<QByteArray,QStringList>::iterator it=mDuplication.begin();it!=mDuplication.end();++it) {
//        if(it.value().count()>1){
//            ui->listWidget->addItem(it.key());

//            qDebug()<<it.value();
//        }
//    }
}

void Widget::onCalcMd5Finished(QHash<QByteArray,QStringList> list){
    mDuplication=list;
    //显示结果
    ui->listWidget->clear();
    for (QHash<QByteArray,QStringList>::iterator it=mDuplication.begin();it!=mDuplication.end();++it) {
        if(it.value().count()>1){
            ui->listWidget->addItem(it.key());

            qDebug()<<it.value();
        }
    }
}

void Widget::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->listWidget_2->clear();
    QStringList currList=mDuplication[currentText.toLocal8Bit()];
    ui->listWidget_2->addItems(currList);
//ui->listWidget_2->addItem()
}

#include <QProcess>
#include <windows.h>

void Widget::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    QString filename=item->text();
//    filename=filename.replace("\\","\\\\");
    //！！使用系统默认打开方式打开文件
//    QStringList param;
//    param << filename;
//    bool started=QProcess::execute("explorer "+filename);


    ShellExecuteW(NULL,QString("open").toStdWString().c_str(),QString(filename).toStdWString().c_str(),NULL,NULL,SW_SHOW);

//    qDebug() <<"start process :"<< filename <<"; result:"<<started;

}

QStringList Widget::getFiles(const QString &path)
{
    QStringList ret;

    QDir dir(path);
    QFileInfoList infoList= dir.entryInfoList(QDir::Files | QDir::Dirs |QDir::NoDotAndDotDot);
    for (int i=0;i<infoList.count();i++) {
        QFileInfo info=infoList.at(i);
        if(info.isDir()){
            QString subDir=info.absoluteFilePath();
            QStringList files=getFiles(subDir);
            ret.append(files);
        }else {
            //absoluteFilePath：如果是目录，返回目录路径，如果是文件返回文件路径
            QString filename=info.absoluteFilePath();
            ret.append(filename);
        }
    }
    return ret;
}

