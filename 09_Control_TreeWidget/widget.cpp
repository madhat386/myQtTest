#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    //treeWidget的使用
    //添加头
    ui->treeWidget->setHeaderLabels(QStringList() << "英雄" << "英雄介绍");

    //添加项目
    QTreeWidgetItem* liItem = new QTreeWidgetItem(QStringList() << "力量");
    ui->treeWidget->addTopLevelItem(liItem);



}

Widget::~Widget() {
    delete ui;
}
