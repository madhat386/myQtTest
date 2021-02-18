#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    connect(ui->btn_get, &QPushButton::clicked, [ = ]() {
        qDebug() << ui->smallWidget->getValue();
    });

    connect(ui->btn_set, &QPushButton::clicked, [ = ]() {
        ui->smallWidget->setValue();
    });

}

Widget::~Widget() {
    delete ui;
}
