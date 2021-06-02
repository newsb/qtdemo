#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// server :再线程中accept、send
#include "mytcpserver.h"
#include <QTcpSocket>

#include <QFile>
#include<QDateTime>
#include<QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnStartListen_clicked();

private:
    Ui::MainWindow *ui;

    MyTCPServer *m_s;
    QFile *mFile;
};
#endif // MAINWINDOW_H
