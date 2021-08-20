#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
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
    void on_btnDownload_clicked();
    void onFinished();
    void onHeaderFinished();
    void onlistFileFinished();
    void onErr(QNetworkReply::NetworkError);
private:
    Ui::MainWindow *ui;

    void startListFile();
    void startGetHeaderSize(const QString url);
    void startDownloadFile(const QString url);
    void onDownloadProgressChange(qint64 bytesReceived, qint64 bytesTotal);
};
#endif // MAINWINDOW_H
