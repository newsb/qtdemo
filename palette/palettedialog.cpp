#include "palettedialog.h"
#include <QGridLayout>
#include <QHBoxLayout>
PaletteDialog::PaletteDialog(QWidget *parent)
    : QDialog(parent) {
    createCtrlFrame();
    createContentFrame();
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(ctrlFrame);
    mainLayout->addWidget(contentFrame);
}

PaletteDialog::~PaletteDialog() {}
void PaletteDialog::createCtrlFrame() {
    ctrlFrame = new QFrame;
    //颜色选择面板
    windowLabel = new QLabel(tr("QPalette::Window: "));
    windowComboBox = new QComboBox;
    fillColorList(windowComboBox);
    connect(windowComboBox, SIGNAL(activated(int)), this, SLOT(ShowWindow()));
    windowTextLabel = new QLabel(tr("QPalette::WindowText: "));
    windowTextComboBox = new QComboBox;
    fillColorList(windowTextComboBox);
    connect(windowTextComboBox, SIGNAL(activated(int)), this, SLOT(ShowWindowText()));
    buttonLabel = new QLabel(tr("QPalette::Button: "));
    buttonComboBox = new QComboBox;

    fillColorList(buttonComboBox);
    connect(buttonComboBox, SIGNAL(activated(int)), this, SLOT(ShowButton()));
    buttonTextLabel = new QLabel(tr("QPalette::ButtonText: "));
    buttonTextComboBox = new QComboBox;
    fillColorList(buttonTextComboBox);
    connect(buttonTextComboBox, SIGNAL(activated(int)), this, SLOT(ShowButtonText()));
    baseLabel = new QLabel(tr("QPalette::Base: "));
    baseComboBox = new QComboBox;
    fillColorList(baseComboBox);
    connect(baseComboBox, SIGNAL(activated(int)), this, SLOT(ShowBase()));
    QGridLayout *mainLayout = new QGridLayout(ctrlFrame);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(windowLabel, 0, 0);
    mainLayout->addWidget(windowComboBox, 0, 1);
    mainLayout->addWidget(windowTextLabel, 1, 0);
    mainLayout->addWidget(windowTextComboBox, 1, 1);
    mainLayout->addWidget(buttonLabel, 2, 0);
    mainLayout->addWidget(buttonComboBox, 2, 1);
    mainLayout->addWidget(buttonTextLabel, 3, 0);
    mainLayout->addWidget(buttonTextComboBox, 3, 1);
    mainLayout->addWidget(baseLabel, 4, 0);
    mainLayout->addWidget(baseComboBox, 4, 1);
}

void PaletteDialog::createContentFrame() {
    contentFrame = new QFrame;
    label1 = new QLabel(tr("请选择一个值: "));
    comboBox1 = new QComboBox;
    label2 = new QLabel(tr("请输入字符串: "));
    lineEdit2 = new QLineEdit;
    textEdit = new QTextEdit;
    QGridLayout *TopLayout = new QGridLayout;
    TopLayout->addWidget(label1, 0, 0);
    TopLayout->addWidget(comboBox1, 0, 1);
    TopLayout->addWidget(label2, 1, 0);
    TopLayout->addWidget(lineEdit2, 1, 1);
    TopLayout->addWidget(textEdit, 2, 0, 1, 2);
    OkBtn = new QPushButton(tr("确认"));
    CancelBtn = new QPushButton(tr("取消"));
    QHBoxLayout *BottomLayout = new QHBoxLayout;
    BottomLayout->addStretch(1);
    BottomLayout->addWidget(OkBtn);
    BottomLayout->addWidget(CancelBtn);
    QVBoxLayout *mainLayout = new QVBoxLayout(contentFrame);
    mainLayout->addLayout(TopLayout);
    mainLayout->addLayout(BottomLayout);
}
void PaletteDialog::ShowWindow() {
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[windowComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Window, color);
    contentFrame->setPalette(p);
    contentFrame->update();
}
void PaletteDialog::ShowWindowText() {
    QStringList colorList = QColor::colorNames();
    QColor color = colorList[windowTextComboBox->currentIndex()];
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::WindowText, color);
    contentFrame->setPalette(p);
}
// ShowButton()函数响应对按钮背景色的选择:
void PaletteDialog::ShowButton() {
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Button, color);
    contentFrame->setPalette(p);
    contentFrame->update();
}
void PaletteDialog::ShowButtonText() {
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonTextComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::ButtonText, color);
    contentFrame->setPalette(p);
}
// ShowBase()函数响应对可输入文本框背景色的选择:
void PaletteDialog::ShowBase() {
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[baseComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Base, color);
    contentFrame->setPalette(p);
}
// fillColorList()函数用于插入颜色:
void PaletteDialog::fillColorList(QComboBox *comboBox) {
    QStringList colorList = QColor::colorNames();
    QString color;
    foreach (color, colorList) {
        QPixmap pix(QSize(70, 20));
        pix.fill(QColor(color));
        comboBox->addItem(QIcon(pix), NULL);
        comboBox->setIconSize(QSize(70, 20));
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}
