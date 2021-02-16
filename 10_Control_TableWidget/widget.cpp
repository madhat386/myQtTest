#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

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

    for (int i = 0; i < 5; ++i) {
        int col = 0;
        table->setItem(i, col++, new QTableWidgetItem(nameList[i]));
        table->setItem(i, col++, new QTableWidgetItem(genderList[i]));
        table->setItem(i, col, new QTableWidgetItem(QString::number(10 + i)));
    }

    //点击按钮添加赵云
    connect(ui->btnAdd, &QPushButton::clicked, [ = ]() {
        //先判断有没赵云，有就不添加，没有采取添加
        QList<QTableWidgetItem*> reslist = ui->tableWidget->findItems("赵云", Qt::MatchStartsWith);
        if(reslist.empty()) {
            //添加赵云
            table->insertRow(0);
            table->setItem(0, 0, new QTableWidgetItem("赵云"));
            table->setItem(0, 1, new QTableWidgetItem("男"));
            table->setItem(0, 2, new QTableWidgetItem(QString::number(18)));
        } else {
            QMessageBox::warning(this, "警告", "这个武将已经添加过了,请勿重复添加");
        }
    });

    connect(ui->btnDelete, &QPushButton::clicked, [ = ]() {
        QList<QTableWidgetItem*> reslist = table->findItems("赵云", Qt::MatchStartsWith);
        if(!reslist.empty()) {
            //删除赵云
            //找到赵云所在的行
            QList<QTableWidgetItem*> reslist = table->findItems("赵云", Qt::MatchStartsWith);
            //删除行
            table->removeRow(reslist.first()->row());
        }
    });


}

Widget::~Widget() {
    delete ui;
}
