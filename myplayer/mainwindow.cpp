#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QThreadPool>
#include "mycountthread.h"
#include "mycountthreadwork.h"
#include "myrunnablework.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _pMediaPlayer = new QMediaPlayer(this);
    _pMediaPlaylist = new QMediaPlaylist(_pMediaPlayer);
    _pMediaPlayer->setVideoOutput(ui->widget);


      qDebug() << "主线程对象地址:  " << QThread::currentThread();
// 创建子线程 方法1
    MyCountThread* subThread = new MyCountThread;
    connect(subThread, &MyCountThread::curNumber, this, [=](int num) {
        ui->label->setNum(num);
    });
    connect(ui->startBtn, &QPushButton::clicked, this, [=]() {
        // 启动子线程
        subThread->start();
    });

// 创建子线程 方法2
      QThread* sub = new QThread;
      // 创建工作的类对象
      // 千万不要指定给创建的对象指定父对象
      // 如果指定了: QObject::moveToThread: Cannot move objects with a parent
      MyCountThreadWork* work = new MyCountThreadWork;
      // 将工作的类对象移动到创建的子线程对象中
      work->moveToThread(sub);
      // 启动线程
      sub->start();
      // 让工作的对象开始工作, 点击开始按钮, 开始工作
      connect(ui->startBtn2, &QPushButton::clicked, work, &MyCountThreadWork::working);
      // 显示数据
      connect(work, &MyCountThreadWork::curNumber, this, [=](int num) {
          ui->label2->setNum(num);
      });
        //作者: 苏丙榅
        //链接: https://subingwen.cn/qt/thread/#2-2-%E7%A4%BA%E4%BE%8B%E4%BB%A3%E7%A0%81
        //来源: 爱编程的大丙
        //    著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。




 // 线程池初始化，设置最大线程池数
      QThreadPool::globalInstance()->setMaxThreadCount(4);
      // 添加任务
      MyRunnableWork* task = new MyRunnableWork;
      QThreadPool::globalInstance()->start(task);




      // 给窗口设置策略: Qt::DefaultContextMenu
      // 在窗口中按下鼠标右键, 这个事件处理器函数被qt框架调用 QWidget::contextMenuEvent()
//      setContextMenuPolicy(Qt::DefaultContextMenu);


      // 策略 Qt::CustomContextMenu
      // 当在窗口中点击鼠标右键, 窗口会发出一个信号: QWidget::customContextMenuRequested()
      // 对应发射出的这个信号, 需要添加一个槽函数, 用来显示右键菜单
      this->setContextMenuPolicy(Qt::CustomContextMenu);
      connect(this, &MainWindow::customContextMenuRequested, this, [=](const QPoint &pos)
              {
                  // 参数 pos 是鼠标按下的位置, 但是不能直接使用, 这个坐标不是屏幕坐标, 是当前窗口的坐标
                  // 如果要使用这个坐标需要将其转换为屏幕坐标
                  QMenu menu;
                  QAction* act = menu.addAction("C++12");
                  connect(act, &QAction::triggered, this, [=]()
                          {
                              QMessageBox::information(this, "title", "您选择的是C++...");
                          });
                  menu.addAction("Java");
                  menu.addAction("Python");
                  // menu.exec(QCursor::pos());
                  // 将窗口坐标转换为屏幕坐标
                  QPoint newpt = this->mapToGlobal(pos);
                  menu.exec(newpt);
              });


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QString path = QFileDialog::getOpenFileName(this, "打开播放文件", ".", "所有文件(*.*)");
    if(path.isEmpty())
        return;
    qDebug() << __FILE__ << __LINE__ << path;
    _pMediaPlaylist->clear();
    _pMediaPlaylist->addMedia(QUrl::fromLocalFile(path));
    _pMediaPlaylist->setCurrentIndex(0);
    _pMediaPlayer->setPlaylist(_pMediaPlaylist);
    _pMediaPlayer->play();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 判断用户按下的是哪一个鼠标键
//    if(event->button() == Qt::RightButton)
//    {
//        // 弹出一个菜单, 菜单项是 QAction 类型
//        QMenu menu;
//        QAction* act = menu.addAction("C++");
//        connect(act, &QAction::triggered, this, [=]() {
//                    QMessageBox::information(this, "title", "您选择的是C++...");
//                });
//        menu.addAction("Java");
//        menu.addAction("Python");
//        menu.exec(QCursor::pos()); // 右键菜单被模态显示出来了
//    }


//作者: 苏丙榅
//链接: https://subingwen.cn/qt/qt-right-menu/#1-2-%E4%BB%A3%E7%A0%81%E5%AE%9E%E7%8E%B0
//来源: 爱编程的大丙
//    著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
}


// 如果窗口设置了 Qt::DefaultContextMenu 策略,
    // 点击鼠标右键该函数被Qt框架调用
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    // 弹出一个菜单, 菜单项是 QAction 类型
//    QMenu menu;
//    QAction* act = menu.addAction("C++11");
//    connect(act, &QAction::triggered, this, [=]() {
//        QMessageBox::information(this, "title", "您选择的是C++...");
//    });
//    menu.addAction("Java");
//    menu.addAction("Python");
//    menu.exec(QCursor::pos());	// 右键菜单被模态显示出来了


}
