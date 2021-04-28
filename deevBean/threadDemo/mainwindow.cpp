#include "mainwindow.h"
#include<QThread>
class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(QObject *parent = 0)
        : QThread(parent)
    {
    }
protected:
    void run()
    {
        for (int i = 0; i < 1000000000; i++){

        }
        emit done();
    }
signals:
    void done();
};

#include<QVBoxLayout>
#include<QLCDNumber>
#include<QPushButton>
#include<QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    widget->setLayout(layout);
    QLCDNumber * lcdNumber = new QLCDNumber(this);
    layout->addWidget(lcdNumber);
    QPushButton *button = new QPushButton(tr("Start"), this);
    layout->addWidget(button);
    setCentralWidget(widget);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        static int sec = 0;
        lcdNumber->display(QString::number(sec++));
    });

    WorkerThread *thread = new WorkerThread(this);
    connect(thread, &WorkerThread::done, timer, &QTimer::stop);
//    将WorkerThread::deleteLater()函数与WorkerThread::finished()信号连接起来，当线程完成时，系统可以帮我们清除线程实例。
    //finished()信号是系统发出的，与我们自定义的done()信号无关。
    connect(thread, &WorkerThread::finished, thread, &WorkerThread::deleteLater);
    connect(button, &QPushButton::clicked, [=]() {
        timer->start(1);
        thread->start();
    });
}

MainWindow::~MainWindow()
{
}

