#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QThread>
#include <QtConcurrent>
#include <QFile>
#include "MyClass.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    // 带Q_Object宏的类，别放main函数里，部分编译器报错
    qDebug()<<"qApp->thread() :"<< qApp->thread() ;

    qDebug()<<"QThread::currentThread()  :"<< QThread::currentThread() ;
#if 1
    QString filename="D:\\1x.txt";
    QByteArray data="heel";

//    Thread::currentThread()  : QThread(0x17f7690)
//    QtConcurrent  : QThread(0x32f09f0, name = "Thread (pooled)")
    QtConcurrent::run([&filename,&data](){
        qDebug()<<"QtConcurrent  :"<< QThread::currentThread() ;
        QFile file(filename);
        file.open(QIODevice::WriteOnly);
        file.write(data);
        file.waitForBytesWritten(100000);//QFile::waitForBytesWritten() 等待写入完成

    });
#endif
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //QThreadPool:globalInstance()默认线程池，根据cpu核数，分配size
#if 0
    qDebug()<<"default QThreadPool   :"<<
              QThreadPool::globalInstance()->maxThreadCount();
    //自定义线程池,设置size
    QThreadPool threadPool;
    threadPool.setMaxThreadCount(2);
    qDebug()<<"my QThreadPool :"<<
              threadPool.maxThreadCount();
    QSet<int> dataset;
    //互斥锁，lock；unlock；tryLock;
    //lock已经锁定的资源时，卡死等待；tryLock立刻返回不卡死
    //QMutex::Recursive递归模式：连续2个lock不会卡死，
    QMutex mutex (QMutex::Recursive);

    //放入线程池执行
    QtConcurrent::run(&threadPool,[&](){
        //while (true) {
        for(int i=0;i<1000000;i++) {
            mutex.lock();
//            mutex.lock();//第二个lock，锁定一直等待，卡死（使用QMutex::Recursive解决）
            dataset.insert(rand()%1000);
            mutex.unlock();
//            mutex.unlock();
        }
    });
    QtConcurrent::run(&threadPool,[&](){
        //while (true) {
        for(int i=0;i<1000000;i++) {
            mutex.lock();
            auto it=  dataset.find(rand()%1000);
            if(it != dataset.end()){
                dataset.erase(it);
            }
            mutex.unlock();
        }
    });
    QtConcurrent::run(&threadPool,[&](){
        //while (true) {
        for(int i=0;i<1000000;i++) {
            mutex.lock();
            dataset.find(rand()%1000);
            mutex.unlock();
        }
    });
    QtConcurrent::run(&threadPool,[&](){
        //while (true) {
        for(int i=0;i<1000000;i++) {
            mutex.lock();
            dataset.insert(rand()%1000);
            mutex.unlock();
        }
    });
    //等线程池里的都执行完
    threadPool.waitForDone();
    qDebug()<<"waitForDone";

#endif
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //尽量在生存线程中操作对象
    //ui对象，必须在主线程操作（子线程通过信号槽操作主线程ui）
    //connect第五参数，表示信号和槽的通信方式
    //DirectConnection：槽函数运行在发出信号的线程，相当于槽函数直接调用
    //QueuedConnection 队列连接，槽函数运行在接收信号对象的生存线程，依赖事件循环
    //AutoConnection：sender和receiver在同一线程中时是直接连接，否则是队列连接
    Sender sender;
#if 0
    qDebug()<<"main Thread()  :"<< QThread::currentThread() ;


    QtConcurrent::run([&](){
        Receiver receiver;
        QObject::connect(&sender,&Sender::mySignal,
                 &receiver,&Receiver::onReceive
                 //,Qt::DirectConnection //导致槽函数运行于主线程
    //main Thread()  : QThread(0x19e7690)
    //currentThread: QThread(0x19e7690)

    //              ,Qt::QueuedConnection //槽函数运行于子线程
    // main Thread()  : QThread(0x1b57690)
    // currentThread: QThread(0x3580570, name = "Thread (pooled)")

                ,Qt::AutoConnection//子线程中执行
    //main Thread()  : QThread(0x19e7690)
    //currentThread: QThread(0x31a0590, name = "Thread (pooled)")
                 );

        //run函数默认开启事件循环？？
        //开启事件循环
        QEventLoop eventLoop;
        eventLoop.exec();
    });
    QThread::sleep(1);
    emit sender.mySignal();
#endif

    //////////////  //////////////  //////////////  //////////////  //////////////
#if 0
    QtConcurrent::run([&](){
         Receiver receiver;
         //移到主线程执行
         receiver.moveToThread(qApp->thread());
    //main Thread()  : QThread(0x1a97690)
    //currentThread: QThread(0x1a97690)
         QObject::connect(&sender,&Sender::mySignal,
                 &receiver,&Receiver::onReceive
                 ,Qt::QueuedConnection
         );

         QEventLoop eventLoop;
         eventLoop.exec();
    });


    QThread::sleep(1);
    emit sender.mySignal();

    //使用队列连接（Qt::QueuedConnection），
    //即使再同一线程中，也可以让mySignal1，2，3异步执行，
    //而不等1执行完，再执行2，2执行玩再执行3
    //    emit sender.mySignal1();
    //    emit sender.mySignal2();
    //    emit sender.mySignal3();
#endif
#if 0
    QSet<int> data;
    QMutex mutex;
    QThreadPool threadPool;
    threadPool.setMaxThreadCount(2);

    mutex.lock();
    QtConcurrent::run(&threadPool,[&](){
        //循环等待添加完成
        while (true) {
            if(!mutex.tryLock()){
                 qDebug()<<"wait more";
            }else{
                break;
            }
            QThread::msleep(100);
        }

        qDebug()<<"wait finish，start erase";
        for (int i=0;i<5000000;i++){
           auto it=data.find(rand()%1000);
//           QSet<int>::const_iterator it=data.find(rand()%1000);
           if(it!=data.end()){
               data.erase(it);
           }
        }
        qDebug()<<" erase finish";

    });

//    QThread::sleep(3);

    //插入数据
    QtConcurrent::run(&threadPool,[&](){
       for (int i=0;i<5000000;i++){
           data.insert(rand()%1000);
       }
       mutex.unlock();//插入完成，解锁
           qDebug()<<"insert finish";
    });


    //等线程池里的都执行完
    threadPool.waitForDone();
    qDebug()<<"waitForDone";
#endif


    QtConcurrent::run([&](){
         // QMetaObject::invokeMethod 不经过信号
         //，直接跨线程调用槽函数,在主线程调用
        //         invokeMethod还可以调用qml函数
        //qApp->thread() : QThread(0x1b57690)
        //QThread::currentThread()  : QThread(0x1b57690)
        //helloThreadSlot : QThread(0x1b57690)
        QMetaObject::invokeMethod(&sender,
              "helloThreadSlot",
              Qt::QueuedConnection);
    });


    //重载函数connect的时候，直接强转函数指针
    //connect(ui->combobox
//    ,(void(QCombobox::*)(int))&QCombobox::currentIndexChange
//    ,this,&MainWindow::mySlot);

    w.show();
    return a.exec();
}
