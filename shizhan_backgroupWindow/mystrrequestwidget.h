#ifndef MYSTRREQUESTWIDGET_H
#define MYSTRREQUESTWIDGET_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include <QLabel>

namespace Ui {
class MyStrRequestWidget;
}

class MyStrRequestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyStrRequestWidget(QWidget *parent = nullptr);
    ~MyStrRequestWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MyStrRequestWidget *ui;
private:

    QString doRequest(const QString &url);
};

#endif // MYSCROLLBARWIDGET_H
