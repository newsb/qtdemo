#include <QObject>

class QNetworkReply;

class NetWorker : public QObject
{
    Q_OBJECT
public:
    static NetWorker * instance();
    ~NetWorker();

    // 我们的NetWorker只有一个get函数，顾名思义，这个函数会执行 HTTP GET 操作；一个信号finished()，会在获取到服务器响应后发出。
    QNetworkReply * get(const QString &url);
signals:
    void finished(QNetworkReply *reply);
private:
    /*
        这里声明了一个NetWorker的内部类，然后声明了这个内部类的 d 指针。
        d 指针是 C++ 程序常用的一种设计模式。它的存在于 C++ 程序的编译有关。
        在 C++ 中，保持二进制兼容性非常重要。
        如果你能够保持二进制兼容，则当以后升级库代码时，
        用户不需要重新编译自己的程序即可直接运行
        （如果你使用 Qt5.0 编译了一个程序，这个程序不需要重新编译就可以运行在 Qt5.1 下，这就是二进制兼容；
            如果不需要修改源代码，但是必须重新编译才能运行，则是源代码兼容；
            如果必须修改源代码并且再经过编译，例如从 Qt4 升级到 Qt5，则称二者是不兼容的）。
        保持二进制兼容的很重要的一个原则是不要随意增加、删除成员变量。
        因为这会导致类成员的寻址偏移量错误，从而破坏二进制兼容。
        为了避免这个问题，我们将一个类的所有私有变量全部放进一个单独的辅助类中，
        而在需要使用这些数据的类值提供一个这个辅助类的指针。
        注意，由于我们的辅助类是私有的，用户不能使用它，所以针对这个辅助类的修改不会影响到外部类，从而保证了二进制兼容。
       关于二进制兼容的问题，我们会在以后的文章中更详细的说明，这里仅作此简单介绍。
    */
    class Private;
    friend class Private;
    Private *d;

    //NetWorker是一个单例类，因此它有一个instance()函数用来获得这唯一的实例。
//    作为单例模式，要求构造函数、拷贝构造函数和赋值运算符都是私有的，因此我们将这三个函数都放在 private 块中。

/*
    注意我们增加了一个Q_DECL_EQ_DELETE宏。
        这个宏是 Qt5 新增加的，意思是将它所修饰的函数声明为 deleted（这是 C++11 的新特性）。
        如果编译器支持= delete语法，则这个宏将会展开为= delete，否则则展开为空。

3. =default ：要求编译器生成默认的构造，不要因为程序员自己实现编译器就不生成
2. =delete :删除一个函数，删除后函数将无法被使用
    */

    explicit NetWorker(QObject *parent = 0);
    NetWorker(const NetWorker &) Q_DECL_EQ_DELETE;
    NetWorker& operator=(NetWorker rhs) Q_DECL_EQ_DELETE;
};
