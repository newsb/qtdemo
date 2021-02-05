#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QBitmap>
#include <QDebug>
#include <QTimer>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    setWindowTitle("主场景");
    setWindowIcon(QIcon(":/res/coin_48px_title.ico"));
    setFixedSize(323,523);


    //创建开始按钮
    mStartBtn=new MyPushButton(":/res/play_button.png");
    mStartBtn->setParent(this);
    mStartBtn->move((width()-mStartBtn->width())/2,(height()-mStartBtn->height())-40);
    connect(mStartBtn,&QPushButton::clicked,[=](){
        //cout <<"进入选关场景";
        mStartBtn->room1();
        mStartBtn->room2();

        mScene2=new ChooseScene();
        QTimer::singleShot(500,[=](){
           // mScene2->setGeometry(this->x(),this->y(),this->width(),this->height());
            mScene2->show();
            this->hide();
        });
        connect(mScene2,&ChooseScene::quitSignal,[=](){
           // this->setGeometry(mScene2->x(),mScene2->y(),mScene2->width(),mScene2->height());
            this->show();
            mScene2->hide();
        });

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPixmap pixmap;
    bool ret= pixmap.load(":/res/background.jpg");
    if(!ret){
        QString str=QString("res load failed:%1").arg(":/res/background.jpg");
        cout << str;
    }
    pixmap=pixmap.scaled(width(),height());
    p.drawPixmap(0,0,pixmap);

    pixmap.load(":/res/f.png");
    if(!ret){
        QString str=QString("res load failed:%1").arg(":/res/f.png");
        cout << str;
    }
    pixmap=pixmap.scaled(width(),height()*0.75);
    p.drawPixmap(0,0,pixmap);
}

