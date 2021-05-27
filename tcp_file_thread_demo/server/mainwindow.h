#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// server :再线程中accept、send
#include <QTcpServer>
#include <QTcpSocket>

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

    QTcpServer *m_s;
};
#endif // MAINWINDOW_H
