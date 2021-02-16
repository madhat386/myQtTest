#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    //treeWidget的使用
    //添加头
    ui->treeWidget->setHeaderLabels(QStringList() << "英雄" << "英雄介绍");

    //添加项目
    QTreeWidgetItem* liItem1 = new QTreeWidgetItem(QStringList() << "力量");
    QTreeWidgetItem* liItem2 = new QTreeWidgetItem(QStringList() << "敏捷");
    QTreeWidgetItem* liItem3 = new QTreeWidgetItem(QStringList() << "智力");
    ui->treeWidget->addTopLevelItem(liItem1);
    ui->treeWidget->addTopLevelItem(liItem2);
    ui->treeWidget->addTopLevelItem(liItem3);


}

Widget::~Widget() {
    delete ui;
}
