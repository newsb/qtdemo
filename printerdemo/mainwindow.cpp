#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>
#include <QColorDialog>
#include <QMatrix>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    img.load(":/res/C.png");
    //    ui->label->setPixmap(QPixmap(":/res/C.png"));
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label_2->setPixmap(QPixmap::fromImage(img));
    connect(ui->textEdit, &QTextEdit::currentCharFormatChanged, [=]() {

    });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {

    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec()) {
        QTextDocument *doc = this->ui->textEdit->document();
        doc->print(&printer);
    }
}

void MainWindow::on_pushButton_2_clicked() {
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = img.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(img.rect());
        painter.drawImage(0, 0, img);
    }
}

void MainWindow::on_pushButton_3_clicked() {
    // 放大2倍显示
    QMatrix martix;
    martix.scale(2, 2);
    QImage img_2 = img.transformed(martix);
    ui->label_3->setPixmap(QPixmap::fromImage(img_2));
}

void MainWindow::on_pushButton_4_clicked() {

    QMatrix martix;
    martix.scale(0.5, 0.5);
    QImage img_2 = img.transformed(martix);
    ui->label_3->setPixmap(QPixmap::fromImage(img_2));
}

void MainWindow::on_pushButton_5_clicked() {

    QMatrix martix;
    martix.rotate(90);
    QImage img_2 = img.transformed(martix);
    ui->label_4->setPixmap(QPixmap::fromImage(img_2));
}

void MainWindow::on_pushButton_6_clicked() {
    //    QMatrix martix;
    //    martix.rotate(90);
    QImage img_2 = img.mirrored(false, true);
    ui->label_5->setPixmap(QPixmap::fromImage(img_2));
}

void MainWindow::on_pushButton_7_clicked() {
    QImage img_2 = img.mirrored(true, false);
    ui->label_6->setPixmap(QPixmap::fromImage(img_2));
}

void MainWindow::on_pushButton_8_clicked() {
    QTextCharFormat fmt;
    fmt.setFontPointSize(ui->spinBox->value());
    fmt.setFontWeight(ui->checkBox->isChecked() ? QFont::Bold : QFont::Normal);
    fmt.setFontItalic(ui->checkBox_2->isChecked());
    fmt.setFontUnderline(ui->checkBox_2->isChecked());

    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_pushButton_9_clicked() {
    QColor color = QColorDialog::getColor(Qt::red, this);
    if (color.isValid()) {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        ui->textEdit->mergeCurrentCharFormat(fmt);

        //设置样色,（设置label背景色）
        //        ui->label_7->setAutoFillBackground(true);
        //        QPalette p = ui->label_7->palette();
        //        // p.setColor(QPalette::Window, color);
        //        p.setBrush(QPalette::Window, color);
        //        ui->label_7->setPalette(p);

        //        ！！！设button不行
        //        ui->pushButton_9->setAutoFillBackground(true);
        //        QPalette p = ui->pushButton_9->palette();
        //        // p.setColor(QPalette::Window, color);
        //        p.setBrush(QPalette::Window, color);
        //        ui->pushButton_9->setPalette(p);

        //        设button
        QPalette palette = ui->frame->palette();
        palette.setColor(QPalette::Button, color);
        ui->frame->setPalette(palette);
        ui->frame->update();
    }
}
