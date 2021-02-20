#include "dialoglist.h"
#include "ui_dialoglist.h"
#include <QToolButton>
#include <QVector>

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
        QToolButton* btn = new QToolButton();
        btn->setText(nameList[i]);
        QPixmap icon = QPixmap(":/images/" + iconNameList[i]);
        btn->setIcon(icon);
        btn->setIconSize(icon.size());
        btn->setAutoRaise(true);
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //添加进如垂直布局中（page_layout）
        ui->page_layout->addWidget(btn);
        v.push_back(btn);
    }






}

DialogList::~DialogList() {
    delete ui;
}
