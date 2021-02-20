#include "widget.h"
#include "ui_widget.h"
#include <QDataStream>
#include <QMessageBox>
#include <QDateTime>

//Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
//    ui->setupUi(this);
//}

Widget::Widget(QWidget* parent, QString name): QWidget (parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    this->name = name;
    this->setWindowTitle(name);
    this->udp = new QUdpSocket(this);
    this->name = name;
    this->port = 8888;
    //采用ShareAddress模式（允许其他的 服务连接到同样的地址和端口，特别是用在多客户端监听同一个服务端口时特别有效）
    //ReuseAddressHint模式（在地址和端口已经被其他套接字绑定的情况下，也应该试着重新绑定）和ShareAddress模式配合使用
    this->udp->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    //发送新用户进入消息
    sendMsg(UsrEnter);
    //绑定发送按钮的点击事件
    connect(ui->sendBtn, &QPushButton::clicked, [ = ]() {
        this->sendMsg(Msg);
    });

    //绑定udp监听事件
    connect(this->udp, &QUdpSocket::readyRead, this, &Widget::receiveMessage);

}



Widget::~Widget() {
    delete ui;
}

//发送消息
void Widget::sendMsg(Widget::MsgType type) {
    //发送消息分为3中类型
    //发送的消息分为三段，第一段类型，第二段具体内容
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << type;
    stream << this->getUsr();
    switch (type) {
        case Msg:
            if (ui->msgTxtEdit->toPlainText().isEmpty()) {
                QMessageBox::warning(this, "警告", "要发送的消息为空");
                return;
            }
            stream << this->getMsg();
            break;
        case UsrEnter:
            stream << "进入了聊天室";
            break;
        case UsrLeft:

            break;
    }

    //书写报文,广播发送(向广播地址发送)
    udp->writeDatagram(array, QHostAddress::Broadcast, this->port);
}

void Widget::usrEnter(QString username) {

}

void Widget::usrLeft(QString username, QString time) {

}

QString Widget::getUsr() {
    return this->name;
}

QString Widget::getMsg() {
    QString str = ui->msgTxtEdit->toHtml();
    ui->msgTxtEdit->clear();
    ui->msgTxtEdit->setFocus();
    return str;
}

//处理接收到udp消息的槽函数
void Widget::receiveMessage() {
    //读取数据报文
    long long size = this->udp->pendingDatagramSize();
    QByteArray array(static_cast<int>(size), 0);
    this->udp->readDatagram(array.data(), size);
    //解析数据（分段）
    QDataStream stream(&array, QIODevice::ReadOnly);
    int msgType;
    stream >> msgType;
//    MsgType type = static_cast<MsgType>(msgType);
    QString receiveName;
    QString receiveMsg;
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    bool isEmpty = false;
    switch (msgType) {
        case Msg:
            stream >> receiveName >> receiveMsg;
            //追加来聊天记录
            ui->msgBrowser->setTextColor(Qt::blue);
            ui->msgBrowser->append("[" + receiveName  + "]" + time);
            ui->msgBrowser->append(receiveMsg);
            break;
        case UsrEnter:
            stream >> receiveName;
            isEmpty = ui->usrTblWidget->findItems(receiveName, Qt::MatchExactly).isEmpty();
            if(isEmpty) {
                //添加上线用户列表
                QTableWidgetItem* usrItem = new QTableWidgetItem(receiveName);
                //插入行
                ui->usrTblWidget->insertRow(0);
                ui->usrTblWidget->setItem(0, 0, usrItem);
                //追加聊天记录
                ui->msgBrowser->setTextColor(Qt::gray);
                ui->msgBrowser->append("用户:" + receiveName + "上线了");
                //在线人数更新
                ui->usrNumLbl->setText(QString("在线用户:%1人").arg(ui->usrTblWidget->rowCount()));
                //把自身的信息广播出去，告诉别人自己在线
                sendMsg(UsrEnter);
            }
            break;
        case UsrLeft:

            break;
    }


}

void Widget::closeEvent(QCloseEvent* e) {
    emit this->closeWidget();
}
