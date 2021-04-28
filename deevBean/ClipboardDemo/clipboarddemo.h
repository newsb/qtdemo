#ifndef CLIPBOARDDEMO_H
#define CLIPBOARDDEMO_H

#include <QWidget>

class ClipboardDemo : public QWidget
{
    Q_OBJECT

public:
    ClipboardDemo(QWidget *parent = nullptr);
    ~ClipboardDemo();
private slots:
    //个类只有两个槽函数，一个是从剪贴板获取内容，一个是给剪贴板设置内容
    void setClipboardContent();
    void getClipboardContent();
};
#endif // CLIPBOARDDEMO_H
