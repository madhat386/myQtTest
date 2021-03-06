#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextCodec>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include <QTextStream>
#include <QDataStream>

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    //点击按钮，选取文件
    connect(ui->pushButton, &QPushButton::clicked, [ = ]() {
        //打开对话框
        QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "C:\\Users\\madha.KAERMORHEN\\Desktop");
        if(filePath.isEmpty()) {
            QMessageBox::warning(this, "警告", "打开文件失败");
        } else {
            //将路径放入到lineEdit中
            ui->lineEdit->setText(filePath);
            //读取文件(所有)
            QFile file(filePath);
            //指定打开方式(只读的方式)
            file.open(QIODevice::ReadOnly);


            //读文件
            //QByteArray arr = file.readAll();
            //在文本编辑框中显示
            //ui->textEdit->setText(arr);//默认支持编码格式utf-8

            //读gbk编码文件
            //QTextCodec* codec = QTextCodec::codecForName("gbk");
            //ui->textEdit->setText(codec->toUnicode(arr));

            QByteArray arr;
            while (!file.atEnd()) {
                //读一行
                arr += file.readLine();
            }
            ui->textEdit->setText(arr);
            //更改打开文件的方式之前需要先关闭文件
            file.close();

            //写文件
            //重新指定打开方式(这里使用追加)
            file.open(QFileDevice::Append);
            file.write("这个是新追加的一行话\n");
            file.flush();

            //关闭文件
            file.close();

            //通过QFileInfo读取文件的信息
            QFileInfo info(filePath);
            QString str = QString("文件名:%1,文件路径:%2,后缀名:.%3,文件大小%4")
                          .arg(info.fileName())
                          .arg(info.filePath())
                          .arg(info.suffix())
                          .arg(info.size())
                          ;
            qDebug() << str;
            qDebug() << "文件创建时间：" << info.birthTime().toString("yyyy-MM-dd hh:mm::ss");
            qDebug() << "文件修改时间：" << info.lastModified().toString("yyyy-MM-dd hh:mm::ss");
        }

    });

    //文件流（数据流和文本流）的方式读写
    //文本流
    QFile file("aaa.txt");
    file.open(QFileDevice::WriteOnly);
    QTextStream stream(&file);
    stream << "hello" << " world123456";
    file.close();

    //流读操作
    file.open(QFileDevice::ReadOnly);
    QString str;
    //这种右移操作符读取碰到空格会停止读取
//    stream >> str;
    str = stream.readAll();
    qDebug() << str;
    file.close();

    //数据流
    QFile file2("bbb.txt");
    file2.open(QFileDevice::WriteOnly);
    QDataStream dataSteam(&file2);
    dataSteam << QString("hello world") << 123456;
    file2.close();

    //读二进制数据流
    file2.open(QFileDevice::ReadOnly);
    QString str2;
    int number;
    dataSteam >> str2 >> number; //一次右移运算读完一个数据块停止
    qDebug() << str2 << number;
    file2.close();



}

Widget::~Widget() {
    delete ui;
}
