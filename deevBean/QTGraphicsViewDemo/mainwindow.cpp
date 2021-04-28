#include "mainwindow.h"
#include <QDragEnterEvent>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    textEdit->setAcceptDrops(false);
    setAcceptDrops(true);

    setWindowTitle(tr("Text Editor"));
}

MainWindow::~MainWindow(){

}
//当用户将对象拖动到组件上面时，系统会回调dragEnterEvent()函数。
void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    if (event->mimeData()->hasFormat("text/uri-list")) {
        //向用户暗示，你可以将拖动的对象放在这个组件上。默认情况下，组件是不会接受拖放的。
        event->acceptProposedAction();
    }
}
//当用户将对象释放到组件上面时，系统回调dropEvent()函数。
void MainWindow::dropEvent(QDropEvent *event){
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }

    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) {
        return;
    }

    if (readFile(fileName)) {
        setWindowTitle(tr("%1 - %2").arg(fileName, tr("Drag File")));
    }

}

bool MainWindow::readFile(const QString &fileName){
    bool r = false;
    QFile file(fileName);
    QString content;
    if(file.open(QIODevice::ReadOnly)) {
        content = file.readAll();
        r = true;
    }
    textEdit->setText(content);
    return r;
}
