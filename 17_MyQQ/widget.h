#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT

    enum MsgType {
        Msg,
        UsrEnter,
        UsrLeft
    };
public:
//    explicit Widget(QWidget* parent = nullptr);
    explicit Widget(QWidget* parent, QString name);
    ~Widget();

    void sendMsg(MsgType type);//广播消息
    void usrEnter(QString username);//处理新用户加入
    void usrLeft(QString username, QString time);//处理用户离开
    QString getUsr();//获取用户名
    QString getMsg();//获取聊天信息

signals:
//关闭窗口发送信号
    void closeWidget();

private:
    Ui::Widget* ui;
    QUdpSocket* udp;
    QString name;//用户名
    qint16 port;//端口

    //重写关闭事件
    void closeEvent(QCloseEvent*);
    void receiveMessage();
};


#endif // WIDGET_H
