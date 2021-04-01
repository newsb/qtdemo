#include <QCoreApplication>
#include <QtTest>

// add necessary includes here

class MyTestCase : public QObject {
    Q_OBJECT

  public:
    MyTestCase();
    ~MyTestCase();

  private slots:
    void test_case1();
};

MyTestCase::MyTestCase() {}

MyTestCase::~MyTestCase() {}

void MyTestCase::test_case1() {}

QTEST_MAIN(MyTestCase)
#include "tst_mytestcase.moc"
