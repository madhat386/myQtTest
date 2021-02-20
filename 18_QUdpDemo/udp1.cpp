#include "udp1.h"
#include "ui_udp1.h"

Udp1::Udp1(QWidget* parent) : QWidget(parent), ui(new Ui::Udp1) {
    ui->setupUi(this);




}

Udp1::~Udp1() {
    delete ui;
}
