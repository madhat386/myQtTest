#include "widget.h"
#include "ui_widget.h"

//Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
//    ui->setupUi(this);
//}

Widget::Widget(QWidget* parent, QString name): QWidget (parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    this->name = name;
    this->setWindowTitle(name);
}

Widget::~Widget() {
    delete ui;
}
