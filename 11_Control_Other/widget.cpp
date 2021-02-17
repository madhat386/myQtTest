#include "widget.h"
#include "ui_widget.h"
#include <QMovie>

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    this->setFixedSize(950, 620);

    //设置默认显示页
    ui->stackedWidget->setCurrentIndex(3);

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

    //为下拉框添加选项
    ui->comboBox->addItem("奔驰");
    ui->comboBox->addItem("宝马");
    ui->comboBox->addItem("拖拉机");

    connect(ui->btn_select, &QPushButton::clicked, [ = ]() {
        //ui->comboBox->setCurrentIndex(2);
        ui->comboBox->setCurrentText("拖拉机");
    });

    //利用QLabel显示图片
    ui->label->setPixmap(QPixmap(":/image/OnePiece.png"));

    //利用QLabel显示动图
    QMovie* movie = new QMovie(":/image/mario.gif");
    ui->label_2->setMovie(movie);
    //播放gif图片
    movie->start();

}

Widget::~Widget() {
    delete ui;
}
