#ifndef PALETTEDIALOG_H
#define PALETTEDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

class PaletteDialog : public QDialog {
    Q_OBJECT

  public:
    PaletteDialog(QWidget *parent = nullptr);
    ~PaletteDialog();

    void createCtrlFrame();          //完成窗体左半部分颜色选择区的创建
    void createContentFrame();       //完成窗体右半部分的创建
    void fillColorList(QComboBox *); //完成向颜色 下拉列表框中插入颜色的工作
  private slots:
    void ShowWindow();
    void ShowWindowText();
    void ShowButton();
    void ShowButtonText();
    void ShowBase();

  private:
    QFrame *ctrlFrame; //颜色选择面板
    QLabel *windowLabel;
    QComboBox *windowComboBox;
    QLabel *windowTextLabel;
    QComboBox *windowTextComboBox;
    QLabel *buttonLabel;
    QComboBox *buttonComboBox;
    QLabel *buttonTextLabel;
    QComboBox *buttonTextComboBox;
    QLabel *baseLabel;
    QComboBox *baseComboBox;
    QFrame *contentFrame; //具体显示面板

    QLabel *label1;
    QComboBox *comboBox1;
    QLabel *label2;
    QLineEdit *lineEdit2;
    QTextEdit *textEdit;
    QPushButton *OkBtn;
    QPushButton *CancelBtn;
};
#endif // PALETTEDIALOG_H
