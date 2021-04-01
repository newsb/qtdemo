#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btnStop_clicked() {
    for (int i = 0; i < MAXSIZE; i++) {
        mMyThreadArr[i]->terminate();
        mMyThreadArr[i]->wait();
    }
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
}

void MainWindow::on_btnStart_clicked() {

    for (int i = 0; i < MAXSIZE; i++) {
        mMyThreadArr[i] = new MyThread();
    }
    for (int i = 0; i < MAXSIZE; i++) {
        mMyThreadArr[i]->start();
    }
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}
