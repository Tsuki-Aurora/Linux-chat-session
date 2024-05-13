#include "sessionwindow.h"
#include "ui_sessionwindow.h"
#include <QApplication>
//#include <QTextCursor>
#include <QWidget>

#include <QVBoxLayout>

#include <QTextEdit>

#include <QSqlDatabase>

#include <QSqlQuery>

#include <QSqlError>

/*----------client和server函数----------*/
#include "chatRoomClient.h"
#include "chatRoomServer.h"

sessionWindow::sessionWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sessionWindow)
{
    ui->setupUi(this);
    // listView 是 QListView* 类型的指针
    //connect(ui->QListView, &QListView::indexesMoved, this, &sessionWindow::on_plainTextEdit_blockCountChanged);
     // 连接按钮的 clicked 信号到槽函数
    connect(ui->pushButton, &QPushButton::clicked, this, &sessionWindow::on_pushButton_clicked);

}

sessionWindow::~sessionWindow()
{
    delete ui;
    shared_data::ShareData::client_message="#exit"; //退出
    //delete MainWindow::server;
}


void sessionWindow::on_pushButton_clicked()
{
    // 从 QLineEdit 获取文本
     QString text= ui->lineEdit->text();
     if(!text.isEmpty())
     {
         ChatRoomClient *client=new ChatRoomClient("127.0.0.1",6000);
         client->InputMessage(); //发送信息函数
         client->RecvMessage(); //回收信息函数
     }
    shared_data::ShareData::client_message=text.toStdString();
    QString other_message=QString::fromStdString(shared_data::ShareData::server_message);

    //消息显示
    /*Test*/
    //QMessageBox::information(this, "Text", "You entered: " + text);
    //这里使用server端返回的数据进行显示
        // 将文本添加到聊天框的末尾，并添加换行符以便新消息在新的一行
    if(!text.isEmpty())
    {
    ui->plainTextEdit->appendPlainText("You:"+text + "\n");
    }
    if(!other_message.isEmpty())
    {
    ui->plainTextEdit->appendPlainText(QString::fromStdString(shared_data::ShareData::server_other_name)+":"+other_message);
    }
    else {
        //QTimer *timer = new QTimer(this);
        //connect(timer, &QTimer::timeout, this,&sessionWindow::on_pushButton_clicked);
        //timer->start(5000); // 延时2000毫秒（即2秒）
        ui->plainTextEdit->appendPlainText(QString::fromStdString(shared_data::ShareData::server_other_name)+":"+other_message);
        //ui->plainTextEdit->appendPlainText("正在重连！！");
    }
    shared_data::ShareData::server_message=text.toStdString();
        // 清除输入框中的内容
    ui->lineEdit->clear();
}

void sessionWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    /*test*/
        //QString text = ui->lineEdit->text();
        // 将其打印到控制台或进行其他处理
        //qDebug() << "Current text in lineEdit:" << text;
}

void sessionWindow::on_plainTextEdit_blockCountChanged(int newBlockCount)
{

}
/*
void sessionWindow::on_listView_indexesMoved(const QList<QModelIndex> &indexes)
{

}
*/


void sessionWindow::on_radioButton_clicked()
{
        //清除所有的内容
        ui->textEdit->clear();
        while (ui->comboBox->count() > 0) {
            ui->comboBox->removeItem(0); // 从索引0开始移除，直到没有项为止
        }
        //ui->comboBox->addItem("djhfhgh");
        /*事实上这里不需要数据库初始化，可以连接数据库，直接进行查找，不过会消耗过大*/
        //sql_Init(); //数据库初始化，也可以直接使用
        /*---------这里可以函数创建-------*/
        //QVBoxLayout *layout = new QVBoxLayout(this);
        //QTextEdit *textEdit = new QTextEdit(this);
        //layout->addWidget(textEdit);
        // 假设数据库已经配置好，这里只是示例代码
         QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // 替换为你的数据库驱动
         db.setHostName("localhost");
         db.setDatabaseName("account_information");
         db.setUserName("root");
         db.setPassword("083911Aa");

            if (!db.open()) {
                // 处理数据库连接错误
                qDebug() << "Error connecting to database: " << db.lastError().text();
                return;
            }

            QSqlQuery query;
            query.prepare("SELECT username FROM infor"); // 假设你的表是users，字段是name
            if (query.exec()) {
                while (query.next()) {
                    QString name = query.value(0).toString();
                    //使用ui进行创建
                    ui->comboBox->addItem(name);
                    on_textEdit_copyAvailable(true);
                    num_textEdit++;
                    ui->textEdit->append(name + "\n"); // 添加每个名字到QTextEdit，并添加换行符
                }
            } else {
                // 处理查询错误
                qDebug() << "Error executing query: " << query.lastError().text();
            }
            db.close(); // 关闭数据库连接
            //加载图片的逻辑
            /*-------------------------------这里有点问题----------------------------*/
            QPixmap pixmap(":/images/background.jpg"); // 注意这里的路径是 qrc 文件中的路径
            if (pixmap.isNull()) {
                // 处理加载失败的情况，比如输出错误信息
                qDebug() << "Failed to load pixmap";
            } else {
                ui->label->setPixmap(pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
}

/*
void sessionWindow::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2)
{

}
*/

void sessionWindow::on_textEdit_copyAvailable(bool b)
{
    if(num_textEdit<1)
    {
    ui->textEdit->append("姓名：");
    }else{
        ui->textEdit->append("\n");
    }


}

void sessionWindow::on_comboBox_activated(const QString &arg1)
{


}

/*拉黑设计*/
void sessionWindow::on_radioButton_3_clicked()
{
    QMessageBox::information(this, "提示", "确认对该人拉黑!");
    QString targetText = ui->comboBox->currentText();
    unmask_to_mask=targetText; //全局变量暂时存储
    if (targetText.isEmpty()) {
        return;
    }

    QTextDocument *doc = ui->textEdit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::Start); //光标回到起始点

    while (!cursor.atEnd()) {
        QTextCursor foundCursor = doc->find(targetText, cursor, QTextDocument::FindWholeWords);
        if (foundCursor.isNull()) {
            // 没有找到更多匹配项，退出循环
            break;
        }
        // 删除匹配的文本
        foundCursor.removeSelectedText();
        // 将 cursor 移动到删除位置之后（通常是删除文本之后的字符）
        cursor = doc->find(QString(), foundCursor); // 向前查找（不设置搜索文本）以移动到下一个位置
    }

    // 删除comboBox中的数据
    qint32 index = ui->comboBox->findText(targetText);
    if (index != -1) { // 如果找到了项
        ui->comboBox->removeItem(index);
    }

}


void sessionWindow::on_textEdit_2_copyAvailable(bool b)
{
    if(num_textEdit_2<1)
    {
    ui->textEdit_2->append("黑名单：");
    }else{
        ui->textEdit_2->append("\n");
    }
}

//取消拉黑的人员
void sessionWindow::on_radioButton_2_clicked()
{
    QString name_Cancle = ui->comboBox_2->currentText();
    if (name_Cancle.isEmpty()) {
        return;
    }
/*
    QTextDocument *doc_blacklist = ui->textEdit_2->document();
    QTextCursor cursor_blacklist = doc_blacklist->find(name_Cancle, QTextDocument::FindWholeWords);
    bool found_blacklist = false;
    while (!cursor_blacklist.isNull()) {
        found_blacklist = true;
        cursor_blacklist.removeSelectedText(); // 删除找到的文本
        cursor_blacklist.movePosition(QTextCursor::NextWord); // 移动到下一个词以继续搜索
        //这里使用find会导致光标移动，导致有些文本无法匹配
        cursor_blacklist = doc_blacklist->find(name_Cancle, QTextDocument::FindWholeWords);
    }
*/
    QTextDocument *doc = ui->textEdit_2->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::Start); //光标回到起始点

    while (!cursor.atEnd()) {
        QTextCursor foundCursor = doc->find(name_Cancle, cursor, QTextDocument::FindWholeWords);
        if (foundCursor.isNull()) {
            // 没有找到更多匹配项，退出循环
            break;
        }
        // 删除匹配的文本
        foundCursor.removeSelectedText();
        // 将 cursor 移动到删除位置之后（通常是删除文本之后的字符）
        cursor = doc->find(QString(), foundCursor); // 向前查找（不设置搜索文本）以移动到下一个位置
    }
        QMessageBox::information(this, "提示", "确认取消对该人的拉黑");

        QTextDocument *doc_friends = ui->textEdit->document();
        QTextCursor cursor_friends = doc_friends->find(name_Cancle, QTextDocument::FindWholeWords);
        bool found_friends = !cursor_friends.isNull();
        if (!found_friends) {
            ui->textEdit->append(name_Cancle + '\n'); // 在好友名单中添加
            // 假设这里还有其他操作来更新UI或数据
        }


        // 从黑名单列表中删除
        qint32 index_blacklist = ui->comboBox_2->findText(name_Cancle);
        if (index_blacklist != -1) {
            ui->comboBox_2->removeItem(index_blacklist);
        }

        // 如果需要，在好友列表中添加（ui->comboBox是好友列表）
        qint32 index_friends = ui->comboBox->findText(name_Cancle);
        if (index_friends == -1) {
            ui->comboBox->addItem(name_Cancle); // 在好友列表中增加
        }

}

void sessionWindow::on_comboBox_2_activated(const QString &arg1)
{

}

//刷新拉黑名单
void sessionWindow::on_pushButton_2_clicked()
{

    QString targetText = unmask_to_mask;
    unmask_to_mask="";
    if (targetText.isEmpty()) {
        // 没有选择人员
        return;
    }

    QTextDocument *doc = ui->textEdit_2->document();
    QTextCursor cursor = doc->find(targetText, QTextDocument::FindWholeWords);
    bool found = false;

    while (!cursor.isNull()) {
        // 找到了匹配的文本，删除它
        cursor.removeSelectedText();
        found = true;
        // 查找下一个匹配项，注意这里使用cursor而不是doc，因为cursor会自动更新位置
        cursor = doc->find(targetText, cursor, QTextDocument::FindWholeWords);
    }

    if (found) {
        // 找到了匹配的文本，并已经删除
        QMessageBox::information(this, "提示", "此人已经拉黑过了");
    } else {
        // 没有找到匹配的文本，将其添加到textEdit和comboBox中
        ui->textEdit_2->append(targetText + "\n"); // 假设每行一个名字，添加换行符
        // 假设 num_textEdit_2 是一个整数类型的成员变量，用于跟踪行数
        num_textEdit_2++;
        // 可能还需要更新一些 UI 元素以反映这个变化
        ui->comboBox_2->addItem(targetText);
    }
/*
    QString targetText = ui->comboBox->currentText();
    QTextDocument *doc = ui->textEdit->document();
    QTextCursor cursor = doc->find(targetText, QTextDocument::FindWholeWords);
    on_textEdit_2_copyAvailable(true);
    if (!cursor.isNull()) {
        // 找到了文本
        QMessageBox::information(this, "提示","此人已经拉黑过了");


    } else {
        // 没有找到文本
        ui->textEdit_2->append(targetText);
        num_textEdit_2++;
    }
    ui->comboBox_2->addItem(targetText);
*/
}

void sessionWindow::on_label_linkActivated(const QString &link)
{
    
}
