#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
class MyThread : public QThread {
  public:
    MyThread();

    // QThread interface
  protected:
    virtual void run() override;
};

#endif // MYTHREAD_H
