#include "booleanmodel.h"

BooleanModel::BooleanModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    //在构造函数中，我们把根节点的指针赋值为 0，因此我们提供了另外的一个函数setRootNode()，将根节点进行有效地赋值
    rootNode = 0;
}

BooleanModel::~BooleanModel()
{
    //而在析构中，我们直接使用 delete 操作符将这个根节点释放掉。
    delete rootNode;
}

void BooleanModel::setRootNode(Node *node)
{
    //在setRootNode()函数中，首先我们释放原有的根节点，再将根节点赋值。此时我们需要通知所有视图对界面进行重绘，以表现最新的数据
    beginResetModel();
    delete rootNode;
    rootNode = node;
    endResetModel();
}

/*
index()函数用于返回第 row 行，第 column 列，父节点为 parent 的那个元素的QModelIndex对象。
对于树状模型，我们关注的是其 parent 参数。
在我们实现中，如果 rootNode 或者 row 或者 column 非法，直接返回一个非法的QModelIndex。
否则的话，使用nodeFromIndex()函数取得索引为 parent 的节点，
然后使用children属性（这是我们前面定义的Node里面的属性）获得子节点。
如果子节点不存在，返回一个非法值；否则，返回由createIndex()函数创建的一个有效的QModelIndex对象。
对于具有层次结构的模型，只有 row 和 column 值是不能确定这个元素的位置的，
因此，QModelIndex中除了 row 和 column 之外，还有一个void *或者 int 的空白属性，可以存储一个值。
在这里我们就把父节点的指针存入，这样，就可以由这三个属性定位这个元素。
这里的createIndex()第三个参数就是这个内部使用的指针。
所以我们自己定义一个nodeFromIndex()函数的时候要注意使用QModelIndex的internalPointer()函数获得这个内部指针，从而定位我们的节点。
*/
QModelIndex BooleanModel::index(int row, int column,
                                const QModelIndex &parent) const
{
    if (!rootNode || row < 0 || column < 0)
        return QModelIndex();
    Node *parentNode = nodeFromIndex(parent);
    Node *childNode = parentNode->children.value(row);
    if (!childNode)
        return QModelIndex();
    return createIndex(row, column, childNode);
}

int BooleanModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;
    Node *parentNode = nodeFromIndex(parent);
    if (!parentNode)
        return 0;
    return parentNode->children.count();
}

int BooleanModel::columnCount(const QModelIndex & /* parent */) const
{
    return 2;
}

//parent()函数返回子节点所属的父节点的索引。
//我们需要从子节点开始寻找，直到找到其父节点的父节点，这样才能定位到这个父节点，从而得到子节点的位置。
QModelIndex BooleanModel::parent(const QModelIndex &child) const
{
    Node *node = nodeFromIndex(child);
    if (!node)
        return QModelIndex();
    Node *parentNode = node->parent;
    if (!parentNode)
        return QModelIndex();
    Node *grandparentNode = parentNode->parent;
    if (!grandparentNode)
        return QModelIndex();

    int row = grandparentNode->children.indexOf(parentNode);
    return createIndex(row, 0, parentNode);
}
//data()函数则要返回每个单元格的显示值。
QVariant BooleanModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    Node *node = nodeFromIndex(index);
    if (!node)
        return QVariant();

    if (index.column() == 0) {
        switch (node->type) {
        case Node::Root:
            return tr("Root");
        case Node::OrExpression:
            return tr("OR Expression");
        case Node::AndExpression:
            return tr("AND Expression");
        case Node::NotExpression:
            return tr("NOT Expression");
        case Node::Atom:
            return tr("Atom");
        case Node::Identifier:
            return tr("Identifier");
        case Node::Operator:
            return tr("Operator");
        case Node::Punctuator:
            return tr("Punctuator");
        default:
            return tr("Unknown");
        }
    } else if (index.column() == 1) {
        return node->str;
    }
    return QVariant();
}
QVariant BooleanModel::headerData(int section,
                                  Qt::Orientation orientation,
                                  int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0) {
            return tr("Node");
        } else if (section == 1) {
            return tr("Value");
        }
    }
    return QVariant();
}
Node *BooleanModel::nodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        return static_cast<Node *>(index.internalPointer());
    } else {
        return rootNode;
    }
}
