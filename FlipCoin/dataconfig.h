#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QMap>
#include <QObject>
#include <QVector>
class dataConfig : public QObject {
    Q_OBJECT
  public:
    explicit dataConfig(QObject *parent = nullptr);
    QMap<int, QVector<QVector<int>>> mData;
  signals:
  private:
    void insertData(int level, int array1[4][4]);
    void genArr(int array1[4][4]);
};

#endif // DATACONFIG_H
