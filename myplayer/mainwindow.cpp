#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _pMediaPlayer = new QMediaPlayer(this);
    _pMediaPlaylist = new QMediaPlaylist(_pMediaPlayer);
    _pMediaPlayer->setVideoOutput(ui->widget);

}

MainWindow::~MainWindow()
{
    delete ui;
}
#include <QFileDialog>

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
