#include "currencymodel.h"

CurrencyModel::CurrencyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}
int CurrencyModel::rowCount(const QModelIndex & parent) const
{
    return currencyMap.count();
}

int CurrencyModel::columnCount(const QModelIndex & parent) const
{
    return currencyMap.count();
}
//我们首先判断这个角色是不是用于显示的，如果是，则调用currencyAt()函数返回第 section 列的名字；如果不是则返回一个空白的QVariant对象。
QVariant CurrencyModel::headerData(int section, Qt::Orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    return currencyAt(section);
}
QString CurrencyModel::currencyAt(int offset) const
{
    return (currencyMap.begin() + offset).key();
}
void CurrencyModel::setCurrencyMap(const QMap<QString, double> &map)
{
    //当然可以直接设置 currencyMap，但是我们依然添加了beginResetModel()和endResetModel()两个函数调用。
    //这将告诉关心这个模型的其它类，现在要重置内部数据，大家要做好准备。这是一种契约式的编程方式。
    beginResetModel();
    currencyMap = map;
    endResetModel();
}
//第一个是QModelIndex，也就是单元格的位置；第二个是role，也就是这个数据的角色。
// 函数的返回值是QVariant类型。我们首先判断传入的index是不是合法，如果不合法直接返回一个空白的QVariant。
QVariant CurrencyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    //然后如果role是Qt::TextAlignmentRole，也就是文本的对齐方式，返回int(Qt::AlignRight | Qt::AlignVCenter)
//    如果是Qt::DisplayRole，就按照我们前面所说的逻辑进行计算，然后以字符串的格式返回。
    //这时候你就会发现，其实我们在 if…else… 里面返回的不是一种数据类型：if 里面返回的是 int，而 else 里面是QString，这就是QVariant的作用了。
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QString rowCurrency = currencyAt(index.row());
        QString columnCurrency = currencyAt(index.column());
        if (currencyMap.value(rowCurrency) == 0.0) {
            return "####";
        }
        double amount = currencyMap.value(columnCurrency)
                        / currencyMap.value(rowCurrency);
        return QString("%1").arg(amount, 0, 'f', 4);
    }
    return QVariant();
}
//修改一下数据就会发现，当我们修改过一个单元格后，Qt 会自动刷新所有受影响的数据的值。这也正是 model / view 模型的强大之处：对数据模型的修改会直接反映到视图上。
Qt::ItemFlags CurrencyModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    //只有行和列的索引不一致的时候，我们才允许修改
    if (index.row() != index.column()) {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

//不需要知道在实际编辑的过程中，委托究竟做了什么，只需要提供一种方式，告诉 Qt 如何将委托获得的用户输入的新的数据保存到模型中。这一步骤是通过setData()函数实现
bool CurrencyModel::setData(const QModelIndex &index,const QVariant &value, int role)
{
    //检查 index 是否有效，以及从业务来说，行列是否不等，最后还要检查角色是不是Qt::EditRole
    if (index.isValid()&& index.row() != index.column()&& role == Qt::EditRole) {
        QString columnCurrency = headerData(index.column(),Qt::Horizontal, Qt::DisplayRole).toString();
        QString rowCurrency = headerData(index.row(),Qt::Vertical, Qt::DisplayRole).toString();
        currencyMap.insert(columnCurrency,value.toDouble() * currencyMap.value(rowCurrency));
        emit dataChanged(index, index);
        return true;
    }
    //数据修改成功就返回 true，否则返回 false。
    return false;
}
