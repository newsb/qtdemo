#include "sortview.h"
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

SortView::SortView(QWidget *parent) : QWidget(parent)
{
    //首先创建一个QStringListModel对象，其内容是 Qt 预定义的所有颜色的名字（利用QColor::colorNames()获取）
    model = new QStringListModel(QColor::colorNames(), this);
    //然后是QSortFilterProxyModel对象，我们将其原模型设置为刚刚创建的 model，也就是要为这个 model 进行代理；
    modelProxy = new QSortFilterProxyModel(this);
    //使用它的setSourceModel()函数将前面定义的QStringListModel传进去，也就是我们需要对这个 model 进行代理。
    modelProxy->setSourceModel(model);
    //然后将FilterKeyColumn设置为 0，也就是仅仅对第一列进行过滤
    modelProxy->setFilterKeyColumn(0);

    view = new QListView(this);
    //QListView的数据源必须设置为QSortFilterProxyModel，而不是最开始的 model 对象。
    view->setModel(modelProxy);

    QLineEdit *filterInput = new QLineEdit;
    QLabel *filterLabel = new QLabel(tr("Filter"));
    QHBoxLayout *filterLayout = new QHBoxLayout;
    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(filterInput);
    //    过滤选项
    syntaxBox = new QComboBox;
    syntaxBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    syntaxBox->addItem(tr("Regular expression"), QRegExp::RegExp);
    syntaxBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
    syntaxBox->addItem(tr("Fixed string"), QRegExp::FixedString);
    QLabel *syntaxLabel = new QLabel(tr("Syntax"));
    QHBoxLayout *syntaxLayout = new QHBoxLayout;
    syntaxLayout->addWidget(syntaxLabel);
    syntaxLayout->addWidget(syntaxBox);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    layout->addLayout(filterLayout);
    layout->addLayout(syntaxLayout);

    connect(filterInput, SIGNAL(textChanged(QString)),
            this, SLOT(filterChanged(QString)));
}

void SortView::filterChanged(const QString &text)
{
    //首先使用QComboBox的选择值创建一个QRegExp::PatternSyntax对象；
    //然后利用这个语法规则构造一个正则表达式，
    //注意我们在QLineEdit里面输入的内容是通过参数传递进来的，然后设置数据模型代理的过滤表达式。
    QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(
        syntaxBox->itemData(syntaxBox->currentIndex()).toInt());
    QRegExp regExp(text, Qt::CaseInsensitive, syntax);
    modelProxy->setFilterRegExp(regExp);
}
