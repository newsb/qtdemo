#ifndef MYMD5_H
#define MYMD5_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QStringList>

class MyMd5 : public QObject
{
    Q_OBJECT
public:
    bool cancelCalcMd5;
    explicit MyMd5(QObject *parent = nullptr);
//TODO:可以先根据文件的size是否相等，相等的再计算md5，大文件可以先计算前面部分字节的md5值，不相等直接返回。以提升效率
    QByteArray getFileMd5(const QString &filename);
signals:
    void progress_changed(int progress);
    void calcMd5Finished(QHash<QByteArray,QStringList> list);
public slots:
    void onStartCalcMd5(QStringList files);

};

#endif // MYMD5_H
