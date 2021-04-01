#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <string>

#include "mythread.h"
//#define MAXSIZE 10
const int MAXSIZE = 10;
const std::string S = "10";

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MyThread *mMyThreadArr[MAXSIZE];
  private slots:

    void on_btnStop_clicked();

    void on_btnStart_clicked();

  private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
