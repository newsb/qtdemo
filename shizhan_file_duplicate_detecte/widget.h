#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringList>
#include <QHash>

#include <QListWidgetItem>
#include <QThread>
#include "mymd5.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QPoint z;
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void on_btnClose_clicked();
    void on_btnMax_clicked();
    void on_btnMin_clicked();
    void on_pushButton_clicked();

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

private:
    QHash<QByteArray,QStringList> mDuplication;
    QStringList getFiles(const QString &path);
    QThread * myThread;
    MyMd5 *mymd5;

signals:
    void startCalcMd5(QStringList files);
private slots:
    void onMyProgressChanged(int progress);

    void onCalcMd5Finished(QHash<QByteArray,QStringList> list);
};
#endif // WIDGET_H
