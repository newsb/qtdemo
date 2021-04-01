//(1)在modelex.h文件中 创建ModelEx类，继承自QAbstractTableMode
//(3)在源文件“main.cpp"中，将模型和视图关联，具体代码如下:
#include "modelex.h"
#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ModelEx modelEx;
    QTableView view;
    view.setModel(&modelEx);
    view.setWindowTitle(QObject::tr("modelEx"));
    view.resize(400, 400);
    view.show();

    return a.exec();
}
