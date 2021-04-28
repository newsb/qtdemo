#include "networker.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>
/*
Private是NetWorker的内部类，扮演者前面我们所说的那个辅助类的角色。
NetWorker::Private类主要有一个成员变量QNetworkAccessManager *，把QNetworkAccessManager封装起来。
NetWorker::Private需要其被辅助的类NetWorker的指针，目的是作为QNetworkAccessManager的 parent，
以便NetWorker析构时能够自动将QNetworkAccessManager析构。
当然，我们也可以通过将NetWorker::Private声明为QObject的子类来达到这一目的。
*/
class NetWorker::Private{
    public:
        Private(NetWorker *q) :
              manager(new QNetworkAccessManager(q)) {}

        QNetworkAccessManager *manager;
};

NetWorker *NetWorker::instance(){
    //声明了一个 static 变量，将其指针返回.
    //这是 C++ 单例模式的最简单写法，由于 C++ 标准要求类的构造函数不能被打断，因此这样做也是线程安全的。!!!
    static NetWorker netWorker;
    return &netWorker;
}
/*构造函数参数列表我们将 d 指针进行赋值。
 * 构造函数内容很简单，我们将QNetworkAccessManager的finished()信号进行转发。
 * 也就是说，当QNetworkAccessManager发出finished()信号时，NetWorker同样会发出自己的finished()信号。
 * 析构函数将 d 指针删除。
 * */
NetWorker::NetWorker(QObject *parent) :
      QObject(parent),
      d(new NetWorker::Private(this))
{
    connect(d->manager, &QNetworkAccessManager::finished,
            this, &NetWorker::finished);
}
//由于 NetWorker::Private是在堆上创建的，并且没有继承QObject，所以我们必须手动调用delete运算符。
NetWorker::~NetWorker()
{
    delete d;
    d = 0;
}
QNetworkReply * NetWorker::get(const QString &url)
{
   // 将用户提供的 URL 字符串提供给底层的QNetworkAccessManager，实际上是将操作委托给底层QNetworkAccessManager进行。
   return  d->manager->get(QNetworkRequest(QUrl(url)));
}
