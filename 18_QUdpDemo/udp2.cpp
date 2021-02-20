#include "udp2.h"
#include "ui_udp2.h"

Udp2::Udp2(QWidget* parent) : QWidget(parent), ui(new Ui::Udp2) {
    ui->setupUi(this);

    //设置默认的端口和ip（可以更改）
    ui->myPort->setText("9999");
    ui->toPort->setText("8888");
    ui->toIp->setText("127.0.0.1");

    //初始化套接字
    this->udp = new QUdpSocket(this);
    unsigned short port = static_cast<unsigned short>( ui->myPort->text().toShort());
    udp->bind(port);

    //点击按钮发送消息
    connect(ui->sendBtn, &QPushButton::clicked, [ = ]() {
        udp->writeDatagram(ui->inputField->toPlainText().toUtf8(),
                           QHostAddress(ui->toIp->text()),
                           static_cast<unsigned short>( ui->toPort->text().toInt()));
        ui->record->append("ME:" + ui->inputField->toPlainText());
        ui->inputField->clear();
    });

    //绑定套接字接收数据触发的事件
    connect(udp, &QUdpSocket::readyRead, [ = ]() {
        long long size = udp->pendingDatagramSize();
        QByteArray array(static_cast<int>(size), 0);
        udp->readDatagram(array.data(), size);
        //将数据同步到聊天记录中
        ui->record->append(array);
    });

}

Udp2::~Udp2() {
    delete ui;
}
