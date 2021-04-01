#ifndef MODELEX_H
#define MODELEX_H

#include <QAbstractTableModel>
#include <QMap>
#include <QStringList>
#include <QVector>

class ModelEx : public QAbstractTableModel {
  public:
    explicit ModelEx(QObject *parent = 0);
    // rowCount\columnCount\headerData是QAbstractTableModel的纯虚方法
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  signals:
  public slots:
  private:
    QVector<short> army;
    QVector<short> weaponType;
    //保存数字-文字映射
    QMap<short, QString> armyMap;
    QMap<short, QString> weaponTypeMap;
    QStringList weapon;
    QStringList header;
    //表格初始化填充
    void populateModel();
};

#endif // MODELEX_H
