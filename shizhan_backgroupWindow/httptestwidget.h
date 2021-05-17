#ifndef HTTPTESTWIDGET_H
#define HTTPTESTWIDGET_H

#include <QWidget>


#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include <QLabel>

class HttpTestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HttpTestWidget(QWidget *parent = nullptr);

signals:


    // QWidget interface
//protected:
//    virtual void paintEvent(QPaintEvent *event) override;

private:
    QPixmap mPix;
    QImage downloadImage(const QString &url);
//public slots:
    void doHttpErr(QNetworkReply::NetworkError code);

//    QLabel *imageLabel;
//     QScrollArea *m_ScrollArea;
};

#endif // HTTPTESTWIDGET_H
