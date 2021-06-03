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

    void on_chbUseProxy_stateChanged(int arg1);

    void on_btnTest_clicked();

    void on_cbbProxyType_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

//    QTcpSocket *m_socket;
    QString getProxyCfg();

signals:

    void startConnect(QString ip,quint16 port,bool useProxy=false,int proxyType=0,QString proxyIp="",quint16 proxyPort=0,QString proxyUsr="",QString proxyPwd="");
    void startSendFile(QString path);
    void startTestProxyConnection(QString proxyIp,quint16 proxyPort,QString proxyUsr,QString proxyPwd);
};



#endif // MAINWINDOW_H
