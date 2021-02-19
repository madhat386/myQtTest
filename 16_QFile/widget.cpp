#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextCodec>

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

        }
    });

}

Widget::~Widget() {
    delete ui;
}
