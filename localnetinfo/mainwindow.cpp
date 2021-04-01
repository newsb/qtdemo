#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include <QHostInfo>
#include <QNetworkInterface>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QString localHostName = QHostInfo::localHostName();
    ui->lineEdit->setText(localHostName);
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> listAddress = hostInfo.addresses();
    ui->listWidget->clear();
    for (int i = 0; i < listAddress.count(); i++) {
        ui->listWidget->addItem(listAddress[i].toString());
    }
    connect(ui->btn1, &QPushButton::clicked, this, &MainWindow::getNetDetail);
}
void MainWindow::getNetDetail() {
    QString detail = "";
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    for (int i = 0; i < list.count(); i++) {
        QNetworkInterface interface = list.at(i);
        detail += tr("设备：") + interface.name() + "\n";
        detail += tr("设备地址：") + interface.hardwareAddress() + "\n";
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();

        for (int j = 0; i < entryList.count(); i++) {
            QNetworkAddressEntry entry = entryList.at(j);
            detail += "\t" + tr("IP地址：") + entry.ip().toString() + "\n";
            detail += "\t" + tr("子网掩码：") + entry.netmask().toString() + "\n";
            detail += "\t" + tr("广播地址：") + entry.broadcast().toString() + "\n";
        }
        detail += "==================" + QString::number(i) + "=========================\n";
    }
    QMessageBox::information(this, tr("Detail"), detail);
}

MainWindow::~MainWindow() { delete ui; }
