#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include <QSqlError>



#include <QGraphicsDropShadowEffect>

#include "sessionwindow.h"
#include "ShareData.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QPixmap *pix = new QPixmap(":/blue.png");
    QSize sz = ui->label_image->size();
    ui->label_image->setPixmap(pix->scaled(sz));

    //设置阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3, 0);
    shadow->setColor(QColor("#888888"));
    shadow->setBlurRadius(30);
    ui->label_image->setGraphicsEffect(shadow);
    //初始化数据库
    sql_Init();


}

MainWindow::~MainWindow()
{
    delete ui;
    //delete chatClient;
}

void sql_Init()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); // 设置MySQL服务器地址
    db.setDatabaseName("account_information"); // 设置数据库名
    db.setUserName("root"); // 设置数据库用户名
    db.setPassword("083911Aa"); // 设置数据库密码

    if (!db.open()) {
        qDebug() << "Database connection error";
        return; // 如果无法打开数据库连接，则退出函数
    }

    // 创建表
    QString createsql = QString("CREATE TABLE IF NOT EXISTS infor ("
                             "id INT AUTO_INCREMENT PRIMARY KEY,"
                             "username VARCHAR(20) UNIQUE NOT NULL,"
                             "password VARCHAR(20) NOT NULL)");

    QSqlQuery query;
    if (!query.exec(createsql)) {
        qDebug() << "Table create error:" << query.lastError().text();
    } else {
        qDebug() << "Table create success";
    }
    //数据库关闭
    //db.close();
}

//登陆
void MainWindow::on_btn_signin_clicked()
{
   sql_Init(); // 这是初始化数据库连接的方法
    //qint32 num;
   //启动server
   //if(shared_data::ShareData::server_open_judgment<1)
   //{

       //server->mainServer();
       //这里server启动
       //server在sessionwindow中关闭，因为代表已经关闭了聊天界面
       //shared_data::ShareData::server_open_judgment++;
   //}


    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    shared_data::ShareData::server_other_name=username.toStdString();
    
    //将输入框中的姓名，密码提取到实时变量中
    //chatClient->regist_name = username.toStdString();
    //chatClient->regist_password = password.toStdString();
    shared_data::ShareData::setSharedValue(username.toStdString(), password.toStdString());
    shared_data::ShareData::client_choice=1; //1是登陆
    //ChatRoomClient *client=new ChatRoomClient("127.0.0.1",6000);
    //client->Client_Run(); //连接服务器
    /*
    if(shared_data::ShareData::server_choice==2)
    {
        QMessageBox::information(this, "登录认证", "登录失败, 查询执行错误：");
    }else if (shared_data::ShareData::server_choice==3){

        QMessageBox::information(this, "登录认证", "登录成功, 查询执行成功：");
        sessionWindow *SessionWindow = new sessionWindow(this); // 使用 this 作为父对象
        SessionWindow->show(); // 显示新的界面
        //this->close();//关闭界面
    }
    */

    //QString hashedPassword = hashPassword(password); // 假设这是哈希密码的方法
    /*2.String转换QString

    QString qstr2 = QString::fromStdString(s);
     */
    /*Test*/
    //QString s=QString::fromStdString(shared_data::ShareData::getShared_signing_name());
    //QMessageBox::information(this, "登录认证", s);
    QSqlQuery query;
    query.prepare("SELECT * FROM infor WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    //query.prepare("SELECT id FROM infor WHERE username=username");
    //query.bindValue(":num",num);

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError().text();
        QMessageBox::information(this, "登录认证", "登录失败, 查询执行错误：" + query.lastError().text());
        return;
    }

    if (query.next()) {
        //Currentname = username; // 假设这是全局变量或成员变量
        qDebug() << "Login success";
        QMessageBox::information(this, "登录认证", "登录成功");
        //test
        //QMessageBox::information(this,"编号",QString::number(num));
        // ... 显示聊天窗口 ...
        sessionWindow *SessionWindow = new sessionWindow(this); // 使用 this 作为父对象
        SessionWindow->show(); // 显示新的界面
        //SessionWindow->on_label_linkActivated();
        //this->close(); // 关闭登录界面
    } else {
        qDebug() << "Login error: Username or password incorrect";
        QMessageBox::information(this, "登录认证", "登录失败, 账户或者密码错误");
    }

}

void MainWindow::on_btn_signup_clicked()
{
    this->close();
    Signup *s = new Signup;
    s->show();

}
