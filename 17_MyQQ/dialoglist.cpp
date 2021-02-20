#include "dialoglist.h"
#include "ui_dialoglist.h"

DialogList::DialogList(QWidget* parent) : QWidget(parent), ui(new Ui::DialogList) {
    ui->setupUi(this);



}

DialogList::~DialogList() {
    delete ui;
}
