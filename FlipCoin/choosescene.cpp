#include "choosescene.h"
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QLabel>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

ChooseScene::ChooseScene(QWidget *parent) : QMainWindow(parent)
{


    setWindowTitle("选择关卡场景");
    setWindowIcon(QIcon(":/res/coin_48px_title.ico"));
    setFixedSize(323,523);

    QMenuBar *bar= menuBar();
    QMenu * menu=bar->addMenu("开始");
    QAction *actionQuit = menu->addAction("退出" );
    connect(actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    mBackBtn=new MyPushButton(":/res/back.png",":/res/back3.png");
    mBackBtn->setParent(this);
    mBackBtn->move(width()-mBackBtn->width()-10,height()-mBackBtn->height()-20);

    connect(mBackBtn,&QPushButton::clicked,[=](){

        QTimer::singleShot(500,[=](){
            emit quitSignal();
        });
    });
    pScene=NULL;
    //创建20个关卡
    for(int i=0;i<20;i++){
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelCoin.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,100+(i/4)*70);
        connect(menuBtn,&MyPushButton::clicked,[=](){
            //cout << "选择了第"<<i+1<<"关";
            pScene=new PlayScene(i+1);

            connect(pScene,&PlayScene::quitSignal,[=](){
                //this->setGeometry(pScene->x(),pScene->y(),pScene->width(),pScene->height());
                this->show();
                pScene->hide();

                //每一关卡都不一样，每次都删了重新创建
                delete pScene;
                pScene=NULL;
            });

//            pScene->setGeometry(this->x(),this->y(),this->width(),this->height());
            pScene->show();
            this->hide();
        });
        //显示上面文字，
        QLabel *label=new QLabel;
        label->setParent(this);
        label->move(25+(i%4)*70,100+(i/4)*70);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setFont(QFont("微软雅黑",15,16,true));
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置鼠标穿透属性，点击的时候就不会挡着后面的按钮了
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }



}

void ChooseScene::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPixmap pixmap;
    bool ret= pixmap.load(":/res/background.jpg");
    if(!ret){
        QString str=QString("res load failed:%1").arg(":/res/background.jpg");
        cout << str;
    }
    p.drawPixmap(0,0,pixmap);

    pixmap.load(":/res/f.png");
    if(!ret){
        QString str=QString("res load failed:%1").arg(":/res/f.png");
        cout << str;
    }
    pixmap=pixmap.scaled(width(),height()*0.33);
    p.drawPixmap(0,0,pixmap);

}
