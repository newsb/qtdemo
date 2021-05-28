#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// server :再线程中accept、send
//#include <QTcpSocket>

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

    void on_btnConnect_clicked();

    void on_btnSelect_clicked();

    void on_btnSend_clicked();

private:
    Ui::MainWindow *ui;

//    QTcpSocket *m_socket;
signals:

    void startConnect(QString ip,quint16 port);
    void startSendFile(QString path);
};
#endif // MAINWINDOW_H
