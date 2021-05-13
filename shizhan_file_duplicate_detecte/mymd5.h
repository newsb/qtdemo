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
    explicit MyMd5(QObject *parent = nullptr);

    QByteArray getFileMd5(const QString &filename);
signals:
    void progress_changed(int progress);
    void calcMd5Finished(QHash<QByteArray,QStringList> list);
public slots:
    void onStartCalcMd5(QStringList files);

};

#endif // MYMD5_H
