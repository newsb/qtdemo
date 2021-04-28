#include "booleanwindow.h"
#include "booleanparser.h"

BooleanWindow::BooleanWindow(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(tr("Boolean expression:"));
    lineEdit = new QLineEdit;

    booleanModel = new BooleanModel(this);

    treeView = new QTreeView;
    treeView->setModel(booleanModel);

    connect(lineEdit, &QLineEdit::textChanged ,
            this, &BooleanWindow::booleanExpressionChanged);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label, 0, 0);
    layout->addWidget(lineEdit, 0, 1);
    layout->addWidget(treeView, 1, 0, 1, 2);
    setLayout(layout);

    setWindowTitle(tr("Boolean Parser"));
}
void BooleanWindow::booleanExpressionChanged(const QString &expr)
{
    BooleanParser parser;
    Node *rootNode = parser.parse(expr);
    booleanModel->setRootNode(rootNode);
}
