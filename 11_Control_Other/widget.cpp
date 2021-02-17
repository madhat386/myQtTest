#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    connect(ui->btn_ScrollArea, &QPushButton::clicked, [ = ]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btn_TabWidget, &QPushButton::clicked, [ = ]() {
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->btn_ToolBar, &QPushButton::clicked, [ = ]() {
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->btn_Other, &QPushButton::clicked, [ = ]() {
        ui->stackedWidget->setCurrentIndex(3);
    });


}

Widget::~Widget() {
    delete ui;
}
