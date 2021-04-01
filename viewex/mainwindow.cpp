#include "mainwindow.h"
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    createAction();
    createMenu();
    setupModel();
    setupView();
    setWindowTitle(tr("View Example"));
    resize(600, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::createAction() {
    openAct = new QAction(tr("打开"), this);
    connect(openAct, SIGNAL(triggered()), this, SLOT(slotOpen()));
    saveAct = new QAction(tr("保存"), this);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(slotSave()));
}

void MainWindow::createMenu() {
    fileMenu = new QMenu(tr("文件"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    menuBar()->addMenu(fileMenu);
}

void MainWindow::setupModel() {
    //新建一个model，设置表头数据
    model = new QStandardItemModel(4, 4, this);
    model->setHeaderData(0, Qt::Horizontal, tr("部门"));
    model->setHeaderData(1, Qt::Horizontal, tr("男"));
    model->setHeaderData(2, Qt::Horizontal, tr("女"));
    model->setHeaderData(3, Qt::Horizontal, tr("退休"));
}

void MainWindow::setupView() {
    splitter = new QSplitter;
    splitter->setOrientation(Qt::Vertical);
    histogram = new HistogramView(splitter);
    histogram->setModel(model);

    table = new QTableView;
    // table设置相同的model
    table->setModel(model);
    // tableview的选择模型
    QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
    table->setSelectionModel(selectionModel);
    //连接选择模型的selectionChanged信号 与 tableview的selectionChanged槽函数，
    //    以便使用自定义的HistogramView对象中的选择改变，能反应到tableview对象的显示上。
    histogram->setSelectionModel(selectionModel);

    splitter->addWidget(table);
    splitter->addWidget(histogram);

    setCentralWidget(splitter);

    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), table,
            SLOT(selectionChanged(QItemSelection, QItemSelection)));

    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), histogram,
            SLOT(selectionChanged(QItemSelection, QItemSelection)));
}

void MainWindow::slotOpen() {
    QString name;
    name = QFileDialog::getOpenFileName(this, "打开", ".", "histogram file(*.txt)");
    if (!name.isEmpty()) {
        openFile(name);
    }
}
void MainWindow::slotSave() {
    QString name;
    name = QFileDialog::getSaveFileName(this, "保存", ".", "histogram file(*.txt)");
    if (!name.isEmpty()) {
        // saveFile(name);
        fileFun(name);
    }
}
void MainWindow::saveFile(QString path) {
    QFile data(path);
    // QFile::Truncate 将原来文件内容清空，
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        // qSetFieldWidth设置字段宽度为10个字符
        // left操作符，是QTextStream定义的
        out << QObject::tr("score:") << qSetFieldWidth(10) << left << 90 << endl;
    }
    data.close();
}

void MainWindow::fileFun(QString) {
    QFile file("binary.dat");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QDataStream out(&file);

    out << QString(tr("贵公司："));
    out << QDate::fromString("1999-03-24", "yyyy-MM-dd");
    out << (qint32)19;
    file.close();

    file.setFileName("binary.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error";
        return;
    }
    QDataStream in(&file);
    QString name;
    QDate birthday;
    qint32 age;
    in >> name >> birthday >> age;
    qDebug() << name << birthday << age;
    file.close();
}

void MainWindow::openFile(QString path) {
    if (path.isEmpty()) {
        return;
    }
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }
    QTextStream stream(&file);
    QString line;
    model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
    int row = 0;
    do {
        line = stream.readLine();
        if (!line.isEmpty()) {
            model->insertRows(row, 1, QModelIndex());
            QStringList pieces = line.split(",", QString::SkipEmptyParts);
            model->setData(model->index(row, 0, QModelIndex()), pieces.value(0));
            model->setData(model->index(row, 1, QModelIndex()), pieces.value(1));
            model->setData(model->index(row, 2, QModelIndex()), pieces.value(2));
            model->setData(model->index(row, 3, QModelIndex()), pieces.value(3));
            row++;
        }
    } while (!line.isEmpty());
    file.close();
}
