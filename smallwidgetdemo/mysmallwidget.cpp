#include "mysmallwidget.h"
#include "ui_mysmallwidget.h"

MySmallWidget::MySmallWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MySmallWidget) {
    ui->setupUi(this);

    //重载版本信号connect 方法1：
    auto signal = QOverload<int>::of(&QSpinBox::valueChanged);
    //重载版本信号connect 方法2：函数指针处理connect重载版本
    //    void (QSpinBox::*signal)(int) = &QSpinBox::valueChanged;
//    重载版本信号connect 方法3：
//connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->horizontalSlider, &QSlider::setValue);
    connect(ui->spinBox, signal, ui->horizontalSlider, &QSlider::setValue);

    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);
}

MySmallWidget::~MySmallWidget() { delete ui; }

void MySmallWidget::setData(int val) { ui->spinBox->setValue(val); }

int MySmallWidget::getData() { return ui->spinBox->value(); }
