#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    this->setFixedSize(600, 400);

    //treeWidget的使用
    //添加头
    ui->treeWidget->setHeaderLabels(QStringList() << "英雄" << "英雄介绍");

    //添加项目
    QTreeWidgetItem* liItem = new QTreeWidgetItem(QStringList() << "力量");
    QTreeWidgetItem* minItem = new QTreeWidgetItem(QStringList() << "敏捷");
    QTreeWidgetItem* zhiItem = new QTreeWidgetItem(QStringList() << "智力");
    ui->treeWidget->addTopLevelItem(liItem);
    ui->treeWidget->addTopLevelItem(minItem);
    ui->treeWidget->addTopLevelItem(zhiItem);

    //追加子项目
    QStringList heroL1 = QStringList() << "刚被猪" << "前排坦克，能在吸收伤害的同时造成可观的范围输出";
    QStringList heroL2 = QStringList() << "船长" << "前排坦克，能肉能输出能控场的全能英雄";
    QStringList heroM1 = QStringList() << "月骑" << "中排物理输出，可以使用分裂利刃攻击多个目标";
    QStringList heroM2 = QStringList() << "小鱼人" << "前排战士，擅长偷取敌人的属性来增强自身战力";
    QStringList heroZ1 = QStringList() << "死灵法师" << "前排法师坦克，魔法抗性较高，拥有治疗技能";
    QStringList heroZ2 = QStringList() << "巫医" << "后排辅助法师，可以使用奇特的巫术诅咒敌人与治疗队友";

    QTreeWidgetItem* li1 = new QTreeWidgetItem(heroL1);
    QTreeWidgetItem* li2 = new QTreeWidgetItem(heroL2);
    QTreeWidgetItem* min1 = new QTreeWidgetItem(heroM1);
    QTreeWidgetItem* min2 = new QTreeWidgetItem(heroM2);
    QTreeWidgetItem* zhi1 = new QTreeWidgetItem(heroZ1);
    QTreeWidgetItem* zhi2 = new QTreeWidgetItem(heroZ2);

    liItem->addChild(li1);
    liItem->addChild(li2);
    zhiItem->addChild(zhi1);
    zhiItem->addChild(zhi2);
    minItem->addChild(min1);
    minItem->addChild(min2);

}

Widget::~Widget() {
    delete ui;
}

