#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMediaPlaylist>

#include <QMediaPlayer>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;


    QMediaPlayer *_pMediaPlayer;
    QMediaPlaylist *_pMediaPlaylist;


    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;

    // QWidget interface
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
};
#endif // MAINWINDOW_H
