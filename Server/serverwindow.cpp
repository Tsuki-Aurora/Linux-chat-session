#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    // 假设 buttonBox 是 ServerWindow 的成员变量
        // 确保在 UI 文件中设置了正确的 objectName
        // 如果不是成员变量，则需要从 ui 中获取它，例如：QDialogButtonBox *buttonBox = ui->findChild<QDialogButtonBox *>("buttonBox");

        // 手动连接 accepted() 信号到 on_buttonBox_accepted() 槽（注意这里不使用自动生成的槽名称）
        connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ServerWindow::on_buttonBox_accepted);

        // 如果需要，也可以连接 rejected() 信号
        // connect(buttonBox, &QDialogButtonBox::rejected, this, &ServerWindow::on_buttonBox_rejected);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}




void ServerWindow::on_buttonBox_accepted()
{
    //初始化Server
    ChatRoomServer *server=new ChatRoomServer();
    server->mainServer();
    QMessageBox::information(this, "提示", "Server已经启动");
}
