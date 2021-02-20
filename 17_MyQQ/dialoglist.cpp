#include "dialoglist.h"
#include "ui_dialoglist.h"
#include <QToolButton>

DialogList::DialogList(QWidget* parent) : QWidget(parent), ui(new Ui::DialogList) {
    ui->setupUi(this);
    this->setWindowTitle("QQ2021");
    this->setWindowIcon(QIcon(":/images/qq.png"));

    //设置头像
    QToolButton* btn = new QToolButton();
    btn->setText("张三");
    QPixmap icon = QPixmap(":/images/ftbz.png");
    btn->setIcon(icon);
    btn->setIconSize(icon.size());
    btn->setAutoRaise(true);
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //添加进如垂直布局中（page_layout）
    ui->page_layout->addWidget(btn);




}

DialogList::~DialogList() {
    delete ui;
}
