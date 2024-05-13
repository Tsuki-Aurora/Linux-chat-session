#include "signup.h"
#include "ui_signup.h"
#include "mainwindow.h"

Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    QPixmap *pix = new QPixmap(":/girl1.png");
    QSize sz = ui->label_image->size();
    ui->label_image->setPixmap(pix->scaled(sz));
}

Signup::~Signup()
{
    delete ui;
}

//返回登录按钮
void Signup::on_btn_return_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    this->close();
}

//注册按钮
void Signup::on_pushButton_2_clicked()
{
    sql_Init();
    shared_data::ShareData::client_choice=0; //注册标识
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passwd->text();
    QString surepass = ui->lineEdit_surepasswd->text();
   // 判断密码是否一致
        if (password == surepass) {
            //这里不再使用QT进行注册，而使用server进行注册
            shared_data::ShareData::regist_name=username.toStdString();
            shared_data::ShareData::regist_password=password.toStdString();
            shared_data::ShareData::client_choice=0; //0是注册
            //ChatRoomClient *client=new ChatRoomClient("127.0.0.1",6000);
            //client->Client_Run(); //连接服务器
            /*
            if(shared_data::ShareData::server_choice==0)
            {
                QMessageBox::information(this, "注册认证", "插入失败！");
            }else if(shared_data::ShareData::server_choice==1)
            {
                QMessageBox::information(this, "注册认证", "插入成功！");
                MainWindow *w = new MainWindow;  //跳转到的登陆界面
                w->show();
                this->close();
            }
            */

            // 准备SQL语句
            QSqlQuery query;
            //QString hashedPassword = hashPassword(password);
            query.prepare("INSERT INTO infor(username, password) VALUES(:username, :password)");
            query.bindValue(":username", username);
            query.bindValue(":password", password); // 注意：这里直接存储明文密码是不安全的，应该存储哈希值

            // 执行SQL语句
            if (!query.exec()) {
                qDebug() << "Error: Could not insert into database";
                qDebug() << query.lastError().text(); // 输出错误信息
                QMessageBox::information(this, "注册认证", "插入失败！");
            } else {
                qDebug() << "Inserted successfully";
                QMessageBox::information(this, "注册认证", "插入成功！");

                MainWindow *w = new MainWindow;
                w->show();
                this->close();
            }

        }
        else {
            QMessageBox::information(this, "注册认证", "两次密码输入不一致");
        }

}
