#include "playscene.h"

#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QRect>
#include <QStringList>
#include <QTimer>

#include "dataconfig.h"
#include "mycoin.h"

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

PlayScene::PlayScene(int index) {
    this->levelIndex = index;
    cout << "进入第" << index << "关";

    setWindowTitle(QString("关卡%1").arg(index));
    setWindowIcon(QIcon(":/res/coin_48px_title.ico"));
    setFixedSize(323, 523);

    QMenuBar *bar = menuBar();
    QMenu *menu = bar->addMenu("开始");
    QAction *actionSave = menu->addAction("存档");
    QAction *actionLoad = menu->addAction("读档");
    QAction *actionQuit = menu->addAction("退出");

    connect(actionQuit, &QAction::triggered, [=]() { this->close(); });

    connect(actionSave, &QAction::triggered, [=]() {
        QString val;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                val += this->coinBtn[i][j]->flag ? "1" : "0";
            }
        }
        QString strLineNewVal = QString("#%1-%2").arg(this->levelIndex).arg(val);
        cout << "strLineNewVal:" << strLineNewVal;
        QString strAll = "";

        QFile file("hmm.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString str = QString("打开文件失败:%1 ;errocde:%2;errorString:%3")
                              .arg("hmm.txt")
                              .arg(file.error())
                              .arg(file.errorString());
            cout << str;
            // QMessageBox::information(this,"加载",str);
            // return;读取失败不退出，继续保存
        } else {
            QString strCurrLineHeader = QString("#%1-").arg(this->levelIndex);

            while (!file.atEnd()) {
                QByteArray line = file.readLine();
                QString str = QString(line);
                cout << str;
                if (str.startsWith(strCurrLineHeader)) {
                    //                foundline=true;
                } else {
                    strAll += str + "\n";
                }
            }
        }
        file.close();
        strAll += strLineNewVal;

        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(strAll.toUtf8());
        file.close();
        QMessageBox::information(this, "保存", "存档完毕");
    });

    connect(actionLoad, &QAction::triggered, [=]() {
        QFile file("hmm.txt");

        if (!file.open(QIODevice::ReadOnly)) {
            QString str = QString("打开文件失败:%1 ;errocde:%2;errorString:%3")
                              .arg("hmm.txt")
                              .arg(file.error())
                              .arg(file.errorString());
            cout << str;
            // QMessageBox::information(this, "加载", str);
            return;
        }
        QString strCurrLineHeader = QString("#%1-").arg(this->levelIndex);
        QString strCurrLine = "";

        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            QString str = QString(line);

            if (str.startsWith(strCurrLineHeader)) {
                strCurrLine = str;
                break;
            }
        }
        file.close();

        //解析行数据：
        strCurrLine = strCurrLine.mid(3);
        if (strCurrLine.size() < 16) {
            cout << "存档已损坏！";
            return;
        }
        // QStringList list=strCurrLine.split("-");

        for (int idx = 0; idx < strCurrLine.size(); idx++) {
            int j = idx % 4;
            int i = idx / 4;

            int currVal = strCurrLine[idx] == "1" ? 1 : 0;
            if (gameArray[i][j] != currVal) {
                gameArray[i][j] = strCurrLine[idx] == "1" ? 1 : 0;
                cout << "idx:" << idx << ",strCurrLine[idx]=" << strCurrLine[idx];
                //重设硬币初始状态
                QString str;
                if (gameArray[i][j] == 1) {
                    str = ":/res/coin0.png";
                } else {
                    str = ":/res/coin5.png";
                }
                this->coinBtn[i][j]->resetImg(str);

                this->coinBtn[i][j]->flag = gameArray[i][j];
            }
        }

        // QMessageBox::information(this, "读档", "加载完毕");
    });

    /* 初始化读档菜单可用性*/
    QFile file("hmm.txt");
    bool foundline = false;
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

            QString strCurrLineHeader = QString("#%1-").arg(this->levelIndex);

            while (!file.atEnd()) {
                QByteArray line = file.readLine();
                QString str = QString(line);
                // cout << str;
                if (str.startsWith(strCurrLineHeader)) {
                    foundline = true;
                }
            }
        }
        file.close();
    }
    //判断加载菜单项是否可点击
    actionLoad->setEnabled(foundline);

    mBackBtn = new MyPushButton(":/res/back.png", ":/res/back3.png");
    mBackBtn->setParent(this);
    mBackBtn->move(width() - mBackBtn->width() - 10, height() - mBackBtn->height() - 20);
    connect(mBackBtn, &QPushButton::clicked, [=]() { QTimer::singleShot(500, [=]() { emit quitSignal(); }); });

    //显示当前关卡号
    QLabel *myLabel = new QLabel();
    myLabel->setParent(this);
    QString str = QString("LEVEL:%1").arg(this->levelIndex);
    myLabel->setText(str);
    QFont font;
    font.setFamily("微软雅黑");
    font.setPointSize(20);
    myLabel->setFont(font);
    myLabel->setGeometry(20, height() - 50, this->width(), 50);
    myLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    myLabel->setStyleSheet("color:yellow;");
    //初始化关卡二维数组
    dataConfig config;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }
    //胜利label
    QLabel *winLabel = new QLabel;
    winLabel->setParent(this);
    QPixmap pix;
    pix.load(":/res/v.png");
    winLabel->setPixmap(pix);
    winLabel->setGeometry(0, 0, pix.width(), pix.height());
    winLabel->move(this->width() * 0.5 - pix.width() * 0.5, -pix.height());

    //创建金币背景
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            QLabel *label = new QLabel();
            QPixmap pix;
            pix.load(":/res/square_rounded.png");
            label->setPixmap(pix);
            label->setGeometry(0, 0, pix.width(), pix.height());
            label->setParent(this);
            label->move(27 + pix.width() * i, 140 + pix.height() * j);

            //创建金币
            QString str;
            if (gameArray[i][j] == 1) {
                str = ":/res/coin0.png";
            } else {
                str = ":/res/coin5.png";
            }
            MyCoin *myCoin = new MyCoin(str);
            myCoin->setParent(this);
            myCoin->move(label->x() + label->width() * 0.5 - myCoin->width() * 0.5,
                         label->y() + label->height() * 0.5 - myCoin->height() * 0.5);

            myCoin->posX = i;
            myCoin->posY = j;
            myCoin->flag = gameArray[i][j];
            this->coinBtn[i][j] = myCoin;
            //点击硬币调用changeFlag
            connect(myCoin, &MyCoin::clicked, [=]() {
                cout << "点击了硬币";

                //点击硬币按钮后，禁用按钮点击状态（切换完成后再启用）
                for (int ii = 0; ii < 4; ii++) {
                    for (int jj = 0; jj < 4; jj++) {
                        this->coinBtn[ii][jj]->isWin = true;
                    }
                }

                myCoin->changeFlag();
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;

                //延迟翻转周围硬币
                QTimer::singleShot(300, this, [=]() {
                    //检查右侧硬币翻转
                    if (myCoin->posX + 1 <= 3) {
                        this->coinBtn[myCoin->posX + 1][myCoin->posY]->changeFlag();
                        gameArray[myCoin->posX + 1][myCoin->posY] =
                            gameArray[myCoin->posX + 1][myCoin->posY] == 0 ? 1 : 0;
                    }
                    //检查左侧硬币翻转
                    if (myCoin->posX - 1 >= 0) {
                        this->coinBtn[myCoin->posX - 1][myCoin->posY]->changeFlag();
                        gameArray[myCoin->posX - 1][myCoin->posY] =
                            gameArray[myCoin->posX - 1][myCoin->posY] == 0 ? 1 : 0;
                    }
                    //检查下侧硬币翻转
                    if (myCoin->posY + 1 <= 3) {
                        this->coinBtn[myCoin->posX][myCoin->posY + 1]->changeFlag();
                        gameArray[myCoin->posX][myCoin->posY + 1] =
                            gameArray[myCoin->posX][myCoin->posY + 1] == 0 ? 1 : 0;
                    }
                    //检查上侧硬币翻转
                    if (myCoin->posY - 1 >= 0) {
                        this->coinBtn[myCoin->posX][myCoin->posY - 1]->changeFlag();
                        gameArray[myCoin->posX][myCoin->posY - 1] =
                            gameArray[myCoin->posX][myCoin->posY - 1] == 0 ? 1 : 0;
                    }

                    //检查是否胜利
                    this->isWin = true;
                    for (int ii = 0; ii < 4; ii++) {
                        for (int jj = 0; jj < 4; jj++) {
                            if (this->coinBtn[ii][jj]->flag == false) {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if (this->isWin) {
                        cout << "游戏胜利!!!";
                        for (int ii = 0; ii < 4; ii++) {
                            for (int jj = 0; jj < 4; jj++) {
                                this->coinBtn[ii][jj]->isWin = true;
                            }
                        }

                        //显示胜利图片
                        QPropertyAnimation *animation = new QPropertyAnimation(winLabel, "geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(
                            QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        animation->setEndValue(
                            QRect(winLabel->x(), winLabel->y() + 114, winLabel->width(), winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start(QAbstractAnimation::DeleteWhenStopped);
                    } else {
                        //检查完是否胜利后，没有胜利启用按钮点击状态
                        for (int ii = 0; ii < 4; ii++) {
                            for (int jj = 0; jj < 4; jj++) {
                                this->coinBtn[ii][jj]->isWin = false;
                            }
                        }
                    }
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *) {
    QPainter p(this);
    QPixmap pixmap;
    bool ret = pixmap.load(":/res/background.jpg");
    if (!ret) {
        QString str = QString("res load failed:%1").arg(":/res/background.jpg");
        cout << str;
    }
    pixmap = pixmap.scaled(width(), height());
    p.drawPixmap(0, 0, pixmap);

    pixmap.load(":/res/f.png");
    if (!ret) {
        QString str = QString("res load failed:%1").arg(":/res/f.png");
        cout << str;
    }
    pixmap = pixmap.scaled(width(), height() * 0.33);
    p.drawPixmap(0, 0, pixmap);
}
