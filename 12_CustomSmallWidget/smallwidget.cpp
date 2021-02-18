#include "smallwidget.h"
#include "ui_smallwidget.h"
#include <QDebug>
#include <qspinbox.h>

SmallWidget::SmallWidget(QWidget* parent) : QWidget(parent), ui(new Ui::SmallWidget) {
    ui->setupUi(this);
    ui->horizontalSlider->setMinimum(1);
    ui->horizontalSlider->setMaximum(100);
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(100);

    void(QSpinBox::*fun)(int) = &QSpinBox::valueChanged;
//    connect(ui->spinBox, fun, [ = ](int val) {
//        qDebug() << val;
//        ui->horizontalSlider->setValue(val * 10);
//    });
    connect(ui->spinBox, fun, ui->horizontalSlider, &QSlider::setValue);
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);

}

SmallWidget::~SmallWidget() {
    delete ui;
}

void SmallWidget::setValue() {
    ui->spinBox->setValue(ui->spinBox->value() / 2);
}

int SmallWidget::getValue() {
    return ui->spinBox->value();
}
