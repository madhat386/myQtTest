#include "widget.h"
#include "ui_widget.h"
#include <QDataStream>
#include <QMessageBox>
#include <QDateTime>
#include <QComboBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>


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

    //绑定退出按钮事件
    connect(ui->exitBtn, &QPushButton::clicked, [ = ]() {
        this->close();
    });

    //辅助功能
    //设置字体
    connect(ui->fontCbx, &QFontComboBox::currentFontChanged, [ = ](const QFont & font) {
        ui->msgTxtEdit->setCurrentFont(font);
        ui->msgTxtEdit->setFocus();
    });


    //设置字号
    void (QComboBox::*comSignal)(const QString&) = &QComboBox::currentIndexChanged;
    connect(ui->sizeCbx, comSignal, [ = ](const QString & fontSizeStr) {
        ui->msgTxtEdit->setFontPointSize(fontSizeStr.toDouble());
        ui->msgTxtEdit->setFocus();
    });

    //加粗
    connect(ui->boldTBtn, &QPushButton::clicked, [ = ](bool checked) {
        if (checked) {
            ui->msgTxtEdit->setFontWeight(QFont::Bold);
        } else {
            ui->msgTxtEdit->setFontWeight(QFont::Normal);
        }
    });

    //倾斜
    connect(ui->italicTBtn, &QPushButton::clicked, [ = ](bool checked) {
        ui->msgTxtEdit->setFontItalic(checked);
    });

    //下划线
    connect(ui->underlineTBtn, &QPushButton::clicked, [ = ](bool checked) {
        ui->msgTxtEdit->setFontUnderline(checked);
    });

    //字体颜色
    connect(ui->colorTBtn, &QPushButton::clicked, [ = ]() {
        QColor color = QColorDialog::getColor(Qt::black);
        ui->msgTxtEdit->setTextColor(color);
    });

    //清空聊天记录
    connect(ui->clearTBtn, &QPushButton::clicked, [ = ]() {
        ui->msgBrowser->clear();
    });

    //保存聊天记录
    connect(ui->saveTBtn, &QPushButton::clicked, [ = ]() {
        QString path = QFileDialog::getSaveFileName(this, "保存聊天记录", "history", "*.txt");
        if(path.isEmpty()) {
            QMessageBox::warning(this, "警告", "未设置正确的保存路径及名称");
            return ;
        }
        if(ui->msgBrowser->document()->isEmpty()) {
            QMessageBox::warning(this, "警告", "没有可以保存的聊天记录");
            return ;
        }

        //开始保存操作
        QFile file(path);
        //打开模式加上换行操作QIODevice::Text
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);
        stream << ui->msgBrowser->toPlainText();//这里只保存纯文本
        file.close();
    });
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
            //do nothing special
            break;
    }

    //书写报文,广播发送(向广播地址发送)
    udp->writeDatagram(array, QHostAddress::Broadcast, this->port);
}

void Widget::usrEnter(QString receiveName) {
    bool isEmpty = ui->usrTblWidget->findItems(receiveName, Qt::MatchExactly).isEmpty();
    //这个判空很重要，否则会陷入死循环
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
}

void Widget::usrLeft(QString receiveName, QString time) {
    //处理有用户离开的事件
    QList<QTableWidgetItem*> items = ui->usrTblWidget->findItems(receiveName, Qt::MatchExactly);
    bool isEmpty = items.isEmpty();
    if(!isEmpty) {
        //如果当前用户在线
        int row = items.first()->row();
        ui->usrTblWidget->removeRow(row);
    }
    ui->msgBrowser->setTextColor(Qt::gray);
    ui->msgBrowser->append(QString("%1于%2离开").arg(receiveName).arg(time));
    ui->usrNumLbl->setText(QString("在线用户:%1人").arg(ui->usrTblWidget->rowCount()));
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
    stream >> receiveName;
    switch (msgType) {
        case Msg:
            stream >> receiveMsg;
            //追加来聊天记录
            ui->msgBrowser->setTextColor(Qt::blue);
            ui->msgBrowser->append("[" + receiveName  + "]" + time);
            ui->msgBrowser->append(receiveMsg);
            break;
        case UsrEnter:
            this->usrEnter(receiveName);
            break;
        case UsrLeft:
            this->usrLeft(receiveName, time);
            break;
    }


}

void Widget::closeEvent(QCloseEvent* e) {
    emit this->closeWidget();
    //发送用户离开事件
    sendMsg(UsrLeft);
    //断开套接字
    this->udp->close();
    this->udp->destroyed();
    QWidget::closeEvent(e);
}
