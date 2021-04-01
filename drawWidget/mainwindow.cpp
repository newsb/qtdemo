#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QToolBar>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    drawWidget = new DrawWidget;
    //新建一个Drawwidget对象
    setCentralWidget(drawWidget); //新建的Drawwidget对象作为主窗口的中央窗体
    createToolBar();
    //实现一个工具栏
    setMinimumSize(600, 400);
    //设置主窗口的最小尺寸
    ShowStyle();
    //初始化线型，设置控件中的当前值作为初始值

    drawWidget->setwidth(widthSpinBox->value());
    // 初始化线宽
    drawWidget->setColor(Qt::black);
    // 初始化颜色
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::createToolBar() {
    QToolBar *toolBar = addToolBar("Tool");
    //为主窗口新建一个工 具栏对象
    styleLabel = new QLabel(tr("线型风格: "));
    //创建线型选择控件
    styleComboBox = new QComboBox;
    styleComboBox->addItem(tr("solidLine"), static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem(tr("DaghLine"), static_cast<int>(Qt ::DashLine));
    styleComboBox->addItem(tr("DotLine"), static_cast<int>(Qt ::DotLine));
    styleComboBox->addItem(tr("DashDotLine"), static_cast<int>(Qt ::DashDotLine));
    styleComboBox->addItem(tr("DashDotDotLine"), static_cast<int>(Qt::DashDotDotLine));
    //关联相应的槽函数
    connect(styleComboBox, SIGNAL(activated(int)), this, SLOT(ShowStyle()));
    widthLabel = new QLabel(tr("线宽: "));
    //创建线宽选择控件

    widthSpinBox = new QSpinBox;
    void (QSpinBox::*fun)(int) = &QSpinBox::valueChanged;
    //        connect(widthSpinBox, SIGNAL(valueChanged(int)), drawWidget, SLOT(setwidth(int)));
    connect(widthSpinBox, fun, drawWidget, SLOT(setwidth(int)));
    colorBtn = new QToolButton;
    //创建颜色选择控件
    QPixmap pixmap(20, 20);
    pixmap.fill(Qt::black);
    colorBtn->setIcon(QIcon(pixmap));
    connect(colorBtn, SIGNAL(clicked()), this, SLOT(ShowColor()));
    clearBtn = new QToolButton();
    //创建清除按钮
    clearBtn->setText(tr("清除"));
    connect(clearBtn, SIGNAL(clicked()), drawWidget, SLOT(clear()));

    toolBar->addWidget(styleLabel);
    toolBar->addWidget(styleComboBox);
    toolBar->addWidget(widthLabel);
    toolBar->addWidget(widthSpinBox);
    toolBar->addWidget(colorBtn);
    toolBar->addWidget(clearBtn);
}

void MainWindow::ShowStyle() {
    drawWidget->setStyle(styleComboBox->itemData(styleComboBox->currentIndex(), Qt::UserRole).toInt());
}

void MainWindow::ShowColor() {
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black), this);
    //使用标准颜色对话框QColorDialog获得一.个颜色值
    if (color.isValid()) {
        drawWidget->setColor(color);
        QPixmap p(20, 20);
        p.fill(color);
        colorBtn->setIcon(QIcon(p));
    }
}
