#include "dialoglist.h"
#include "ui_dialoglist.h"
#include <QMessageBox>
#include <QToolButton>
#include <QVector>
#include "widget.h"


DialogList::DialogList(QWidget* parent) : QWidget(parent), ui(new Ui::DialogList) {
    ui->setupUi(this);
    this->setWindowTitle("QQ2021");
    this->setWindowIcon(QIcon(":/images/qq.png"));

    //准备头像数据
    QList<QString>nameList;
    nameList << "水票奇缘" << "忆梦如澜" << "北京出版人" << "Cherry" << "淡然"
             << "娇娇girl" << "落水无痕" << "青墨暖暖" << "无语";


    QStringList iconNameList; //图标资源列表
    iconNameList << "spqy" << "ymrl" << "qq" << "Cherry" << "dr"
                 << "jj" << "lswh" << "qmnn" << "wy";

    QVector<QToolButton*> v;

    //设置头像
    for (int i = 0; i < 9; ++i) {
        QToolButton* btn = new QToolButton(this);
        btn->setText(nameList[i]);
        QPixmap icon = QPixmap(":/images/" + iconNameList[i]);
        btn->setIcon(icon);
        btn->setIconSize(icon.size());
        btn->setAutoRaise(true);
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //添加进如垂直布局中（page_layout）
        ui->page_layout->addWidget(btn);
        v.push_back(btn);
        isShowV.push_back(false);
    }

    //对9个按钮添加信号槽
    for (int i = 0; i < v.size(); ++i) {
        connect(v.at(i), &QToolButton::clicked, [ = ]() {
            QToolButton* btn = v.at(i);

            //防止重复打开对话框
            if(isShowV.at(i)) {
                QString str = QString("%1的会话框已经打开了，请勿重复打开").arg(btn->text());
                QMessageBox::warning(this, "警告", str);
                return;
            }

            //弹出聊天对话框
            Widget* widget = new Widget(nullptr, btn->text()); //参数nullptr代表以顶层的方式弹出，不依赖于其他窗口
            widget->setWindowIcon(btn->icon());
            widget->show();
            isShowV[i] = true;

            //接收已经打开窗口的关闭信号，并将对应的窗口状态设置为false
            connect(widget, &Widget::closeWidget, [ = ]() {
                this->isShowV[i] = false;
            });
        });
    }




}

DialogList::~DialogList() {
    delete ui;
}
