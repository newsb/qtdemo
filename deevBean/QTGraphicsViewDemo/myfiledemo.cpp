#include "myfiledemo.h"
#include <QDebug>

#include <QLabel>
#include <QListWidget>
#include <QHBoxLayout>
#include <QDir>
#include <QTreeWidget>
#include <QTableWidget>

MyFileDemo::MyFileDemo(QWidget *parent) : QWidget(parent)
{
#if 0
    //写二进制文件，
    QFile file("hmm__file.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    // 写入魔术数字和版本
    out << (quint32)0xA0B0C0D0;//用于标识文件的合法性
    out << (qint32)123;//标识文件的版本
    out.setVersion(QDataStream::Qt_4_0);//Qt 不同版本之间的读取方式可能也不一样。这样，我们就得指定 Qt 按照哪个版本去读。

    out << QString("the answer is");
    //最好使用 Qt 整型来进行读写，比如程序中的qint32。这保证了在任意平台和任意编译器都能够有相同的行为。
    out << (qint32)42;
    file.close(); // 如果不想关闭文件，可以使用 file.flush();

//在读取的时候首先检查这个数字是不是 0xA0B0C0D0。如果不是的话，说明这个文件不是可识别格式，因此根本不需要去继续读取。
    QFile file2("hmm__file.dat");
    file2.open(QIODevice::ReadOnly);
    QDataStream in(&file2);

    // 检查魔术数字
    quint32 magic;
    in >> magic;
    if (magic != 0xA0B0C0D0) {
        return ;//"BAD_FILE_FORMAT";
    }

    // 检查版本
    qint32 version;
    in >> version;
    if (version < 100) {
        return  ;//BAD_FILE_TOO_OLD;
    }
    if (version > 123) {
        return  ;//BAD_FILE_TOO_NEW;
    }

    if (version <= 110) {
        return;//        in.setVersion(QDataStream::Qt_3_2);
    } else {
        in.setVersion(QDataStream::Qt_4_0);
    }

    QString str;
    qint32 x;
    in >> str >> x;
    file2.close();
    qDebug()<<"str=" <<str <<";x="<<x;

#endif
#if 0
    QFile file("file.dat");
    file.open(QIODevice::ReadWrite);

    QDataStream stream(&file);
    QString str = "the answer is 42";
    QString strout;

    stream << str;
    file.flush();
    //    当使用<<操作符输出之后，流的游标已经到了最后，此时你再去读，当然什么也读不到了。所以你需要在输出之后重新把游标设置为 0 的位置才能够继续读取。
    stream.device()->seek(0);
    stream >> strout;
    qDebug()<<"strout=" <<strout;
  #endif
#if 0
    QFile data("file.txt");
    //QIODevice::Truncate	以重写的方式打开，在写入新的数据时会将原有数据全部清除，游标设置在文件开头。
    if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&data);
        out << "The answer is " << 42;
    }

    QFile data2("file.txt");
    if (data2.open(QFile::ReadOnly)) {
        QTextStream in(&data2);
        in.setCodec("UTF-8");//QTextStream的编码格式是 Unicode，如果我们需要使用另外的编码
        QString str;
        int ans = 0;
        in >> str >> ans;
    }
#endif
    /*
    Qt 的容器类都不继承QObject，都提供了隐式数据共享、不可变的特性，并且为速度做了优化，具有较低的内存占用量等。
    另外一点比较重要的，它们是线程安全的。
    这些容器类是平台无关的，即不因编译器的不同而具有不同的实现；隐式数据共享，有时也被称作“写时复制（copy on write）”，
    这种技术允许在容器类中使用传值参数，但却不会出现额外的性能损失。

    最后一点，在一些嵌入式平台，STL 往往是不可用的，这时你就只能使用 Qt 提供的容器类，除非你想自己创建。

    Qt 提供了顺序存储容器：QList，QLinkedList，QVector，QStack和QQueue。
        对于绝大多数应用程序，QList是最好的选择。虽然它是基于数组实现的列表，但它提供了快速的向前添加和向后追加的操作。
        如果你需要链表，可以使用QLinkedList。
        如果你希望所有元素占用连续地址空间，可以选择QVector。
        QStack和QQueue则是 LIFO 和 FIFO 的。

      Qt 还提供了关联容器：QMap，QMultiMap，QHash，QMultiHash和QSet。
    带有“Multi”字样的容器支持在一个键上面关联多个值。
    “Hash”容器提供了基于散列函数的更快的查找，而非 Hash 容器则是基于二分搜索的有序集合。

   另外两个特例：QCache和QContiguousCache提供了在有限缓存空间中的高效 hash 查找。


    QList<T>：这是至今为止提供的最通用的容器类。它将给定的类型 T 的对象以列表的形式进行存储，与一个整型的索引关联。
            QList在内部使用数组实现，同时提供基于索引的快速访问。
            我们可以使用 QList::append()和QList::prepend()在列表尾部或头部添加元素，也可以使用QList::insert()在中间插入。
            相比其它容器类，QList专门为这种修改操作作了优化。QStringList继承自QList<QString>。
    QLinkedList<T>：类似于 QList，除了它是使用遍历器进行遍历，而不是基于整数索引的随机访问。
            对于在中部插入大量数据，它的性能要优于QList。
            同时具有更好的遍历器语义（只要数据元素存在，QLinkedList的遍历器就会指向一个合法元素，相比而言，当插入或删除数据时，QList的遍历器就会指向一个非法值）。

    QVector<T>：用于在内存的连续区存储一系列给定类型的值。在头部或中间插入数据可能会非常慢，因为这会引起大量数据在内存中的移动。
    QStack<T>：这是QVector的子类，提供了后进先出（LIFO）语义。相比QVector，它提供了额外的函数：push()，pop()和top()。
    QQueue<T>：这是QList的子类，提供了先进先出（FIFO）语义。相比QList，它提供了额外的函数：enqueue()，dequeue()和head()。
    QSet<T>：提供单值的数学上面的集合，具有快速的查找性能。
    QMap<Key, T>：提供了字典数据结构（关联数组），将类型 T 的值同类型 Key 的键关联起来。通常，每个键与一个值关联。
            QMap以键的顺序存储数据；如果顺序无关，QHash提供了更好的性能。
    QMultiMap<Key, T>：这是QMap的子类，提供了多值映射：一个键可以与多个值关联。
    QHash<Key, T>：该类同QMap的接口几乎相同，但是提供了更快的查找。QHash以字母顺序存储数据。
    QMultiHash<Key, T>：这是QHash的子类，提供了多值散列。

能够存储在容器中的数据必须是可赋值数据类型。
所谓可赋值数据类型，是指具有默认构造函数、拷贝构造函数和赋值运算符的类型。
绝大多数数据类型，包括基本类型，比如 int 和 double，指针，Qt 数据类型，例如QString、QDate和QTime，都是可赋值数据类型。
但是，QObject及其子类（QWidget、QTimer等）都不是。
也就是说，你不能使用QList<QWidget>这种容器，因为QWidget的拷贝构造函数和赋值运算符不可用。
!!!如果你需要这种类型的容器，只能存储其指针，也就是QList<QWidget *>。

    如果要使用QMap或者QHash，作为键的类型必须提供额外的辅助函数。
    QMap的键必须提供operator<()重载，QHash的键必须提供operator==()重载和一个名字是qHash()的全局函数。


//////////////隐式数据共享//////////////
    QPixmap p1, p2;
    p1.load("image.bmp");
    p2 = p1; // p1 和 p2 共享数据

    QPainter paint;
    paint.begin(&p2); // 从此，p2 与 p1 分道扬镳(因为p2 就要被修改了)
    paint.drawText(0,50, "Hi");
    paint.end();


另外还有一点，对于QList或者QVector，我们应该使用at()函数而不是 [] 操作符进行只读访问。
原因是 [] 操作符既可以是左值又可以是右值，这让 Qt 容器很难判断到底是左值还是右值，这意味着无法进行隐式数据共享；
而at()函数不能作左值，因此可以进行隐式数据共享。

另外一点是，对于begin()，end()以及其他一些非 const 遍历器，由于数据可能改变，因此 Qt 会进行深复制。
为了避免这一点，要尽可能使用const_iterator、constBegin()和constEnd()。



//////////////model/view 架构//////////////
    MVC 是  Model-View-Controller 的简写，即模型-视图-控制器。
    在 MVC 中，
        ·模型负责获取需要显示的数据，并且存储这些数据的修改。每种数据类型都有它自己对应的模型，但是这些模型提供一个相同的 API，用于隐藏内部实现。
        ·视图用于将模型数据显示给用户。对于数量很大的数据，或许只显示一小部分，这样就能很好的提高性能。
        ·控制器是模型和视图之间的媒介，将用户的动作解析成对数据的操作，比如查找数据或者修改数据，然后转发给模型执行，最后再将模型中需要被显示的数据直接转发给视图进行显示。
    MVC 的核心思想是分层，不同的层应用不同的功能。
当 MVC 的 V 和 C 结合在一起，我们就得到了 model/view 架构。
          |-----------------------------------------|
          |--  Model  --  View -- Delegate --|
                  data
    模型与数据源进行交互，为框架中其它组件提供接口。
    这种交互的本质在于数据源的类型以及模型的实现方式。
    视图从模型获取模型索引，这种索引就是数据项的引用。
    通过将这个模型索引反向传给模型，视图又可以从数据源获取数据。
    在标准视图中，委托渲染数据项；在需要编辑数据时，委托使用直接模型索引直接与模型进行交互。
总的来说，model/view 架构将传统的 MV 模型分为三部分：模型、视图和委托。
每一个组件都由一个抽象类定义，这个抽象类提供了基本的公共接口以及一些默认实现。模型、视图和委托则使用信号槽进行交互：

    来自模型的信号通知视图，其底层维护的数据发生了改变；
    来自视图的信号提供了有关用户与界面进行交互的信息；
    来自委托的信号在用户编辑数据项时使用，用于告知模型和视图编辑器的状态。
所有的模型都是QAbstractItemModel的子类。这个类定义了供视图和委托访问数据的接口。
模型并不存储数据本身。
这意味着，你可以将数据存储在一个数据结构中、另外的类中、文件中、数据库中，或者其他你所能想到的东西中。我们将在后面再详细讨论这些内容。
    QAbstractItemModel
    QAbstractItemView
    QAbstractItemDelegate:
    */
#if 0
   QLabel * label = new QLabel(this);
    label->setFixedWidth(70);

   QListWidget * listWidget = new QListWidget(this);

    new QListWidgetItem(QIcon(":/Chrome.png"), tr("Chrome"), listWidget);//向listWidget添加列表项可以
    new QListWidgetItem(QIcon(":/Firefox.png"), tr("Firefox"), listWidget);

    listWidget->addItem(new QListWidgetItem(QIcon(":/IE.png"), tr("IE")));//向listWidget添加列表项可以
    listWidget->addItem(new QListWidgetItem(QIcon(":/Netscape.png"), tr("Netscape")));
    listWidget->addItem(new QListWidgetItem(QIcon(":/Opera.png"), tr("Opera")));
    listWidget->addItem(new QListWidgetItem(QIcon(":/Safari.png"), tr("Safari")));
    listWidget->addItem(new QListWidgetItem(QIcon(":/TheWorld.png"), tr("TheWorld")));
    listWidget->addItem(new QListWidgetItem(QIcon(":/Traveler.png"), tr("Traveler")));

    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setIcon(QIcon(":/Maxthon.png"));
    newItem->setText(tr("Maxthon"));
    listWidget->insertItem(3, newItem);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(listWidget);

    setLayout(layout);

    connect(listWidget, SIGNAL(currentTextChanged(QString)),
            label, SLOT(setText(QString)));
    listWidget->setViewMode(QListView::IconMode);//更改为图标显示

#endif

#if 0
    //////////////QTreeWidget //////////////
    QTreeWidget * treeWidget=new QTreeWidget(this);
//    treeWidget->setColumnCount(1);
    //这次我们没有使用setColumnCount()，而是直接使用QStringList设置了 headers，也就是树的表头。接下来我们使用的还是QStringList设置数据。这样，我们实现的是带有层次结构的树状表格
    QStringList headers;
    headers << "Name" << "Number";
    treeWidget->setHeaderLabels(headers);
//    如果你不需要显示这个表头，可以调用setHeaderHidden()函数将其隐藏。
    treeWidget->setHeaderHidden(true);

    QStringList rootTextList;
    rootTextList << "Root" << "0";
    QTreeWidgetItem *root = new QTreeWidgetItem(treeWidget, rootTextList);

    new QTreeWidgetItem(root,  QStringList() << QString("Leaf 1") << "1");

    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList() << QString("Leaf 2") << "2");

    leaf2->setCheckState(0, Qt::Checked);

    QList<QTreeWidgetItem *> rootList;
    rootList << root;
    treeWidget->insertTopLevelItems(0, rootList);

    treeWidget->show();
#endif
#if 0
    //////////////QTableWidget //////////////

    QTableWidget * tableWidget=new QTableWidget(this);
    tableWidget->setColumnCount(3);
    tableWidget->setRowCount(5);

    //QStringList，设置每一列的标题
    QStringList headers;
    headers << "ID" << "Name" << "Age" << "Sex";
    tableWidget->setHorizontalHeaderLabels(headers);

    //以通过调用setItem()函数来设置表格的单元格的数据。这个函数前两个参数分别是行索引和列索引，这两个值都是从 0 开始的，第三个参数则是一个QTableWidgetItem对象。
    tableWidget->setItem(0, 0, new QTableWidgetItem(QString("0001")));
    tableWidget->setItem(1, 0, new QTableWidgetItem(QString("0002")));
    tableWidget->setItem(2, 0, new QTableWidgetItem(QString("0003")));
    tableWidget->setItem(3, 0, new QTableWidgetItem(QString("0004")));
    tableWidget->setItem(4, 0, new QTableWidgetItem(QString("0005")));
    tableWidget->setItem(0, 1, new QTableWidgetItem(QString("20100112")));

    tableWidget->show();
#endif

}
