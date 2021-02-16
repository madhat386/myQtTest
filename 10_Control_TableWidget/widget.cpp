#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    //QTableWidget使用
    //告诉控件一共有多少列
    QStringList list;
    list << "姓名" << "性别" << "年龄";
    ui->tableWidget->setColumnCount(list.size());
    //设置水平头
    ui->tableWidget->setHorizontalHeaderLabels(list);
    //设置行数
    ui->tableWidget->setRowCount(5);
    //添加内容
    QTableWidget* table = ui->tableWidget;

    //QTableWidgetItem* item = new QTableWidgetItem("亚瑟");
    //table->setItem(0, 0, item);

    QStringList nameList;
    nameList << "亚瑟" << "张三" << "李四" << "王五" << "赵六";
    QStringList genderList;
    genderList << "男" << "女" << "男" << "女" << "男";
    QStringList ageList = QStringList() << "12" << "13" << "14" << "15" << "16";


    for (int i = 0; i < 5; ++i) {
        int col = 0;
        table->setItem(i, col++, new QTableWidgetItem(nameList[i]));
        table->setItem(i, col++, new QTableWidgetItem(genderList[i]));
        table->setItem(i, col, new QTableWidgetItem(ageList.at(i)));
    }



}

Widget::~Widget() {
    delete ui;
}
