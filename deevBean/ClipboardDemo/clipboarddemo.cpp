#include "clipboarddemo.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include <QMessageBox>
#include <QClipboard>

ClipboardDemo::ClipboardDemo(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *northLayout = new QHBoxLayout;
    QHBoxLayout *southLayout = new QHBoxLayout;

    QTextEdit *editor = new QTextEdit;
    QLabel *label = new QLabel;
    label->setText("Text Input: ");
    label->setBuddy(editor);
    QPushButton *copyButton = new QPushButton;
    copyButton->setText("Set Clipboard");
    QPushButton *pasteButton = new QPushButton;
    pasteButton->setText("Get Clipboard");

    northLayout->addWidget(label);
    northLayout->addWidget(editor);
    southLayout->addWidget(copyButton);
    southLayout->addWidget(pasteButton);
    mainLayout->addLayout(northLayout);
    mainLayout->addLayout(southLayout);

    connect(copyButton, SIGNAL(clicked()), this, SLOT(setClipboardContent()));
    connect(pasteButton, SIGNAL(clicked()), this, SLOT(getClipboardContent()));
}
void ClipboardDemo::setClipboardContent()
{
    //使用QApplication::clipboard()函数获得系统剪贴板对象。
    QClipboard *board = QApplication::clipboard();
    //setText()，setImage()或者setPixmap()函数可以将数据放置到剪贴板内，
    //也就是通常所说的剪贴或者复制的操作；使用text()，image()或者pixmap()函数则可以从剪贴板获得数据，也就是粘贴
    board->setText("Text from Qt Application");
}

//QClipboard提供的数据类型很少，如果需要，我们可以继承QMimeData类，通过调用setMimeData()函数让剪贴板能够支持我们自己的数据类型。
void ClipboardDemo::getClipboardContent()
{
    QClipboard *board = QApplication::clipboard();
    QString str = board->text();
    QMessageBox::information(NULL, "From clipboard", str);
}
//QClipboard提供了dataChanged()信号，以便监听剪贴板数据变化。
/*
 * void MyTextEditor::mouseReleaseEvent(QMouseEvent *event)
{
    QClipboard *clipboard = QApplication::clipboard();
//supportsSelection()函数在 X11 平台返回 true，其余平台都是返回 false
    if (event->button() == Qt::MidButton
            && clipboard->supportsSelection()) {
        QString text = clipboard->text(QClipboard::Selection);
        pasteText(text);
    }
}*/
ClipboardDemo::~ClipboardDemo()
{
}

