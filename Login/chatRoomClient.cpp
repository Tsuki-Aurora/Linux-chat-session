
#include "chatRoomClient.h"


/*修改main函数中的内容*/
// 使用std::shared_ptr的智能指针变量声明
std::shared_ptr<ChatRoomClient> crc_ptr;
    /*add 4.30*/
// 检查命令行参数
bool check_command_line_arguments(int argc, char const *argv[]) {
    if (argc != 3) {
        printf("No ip and port\nUsing example: ./client 192.168.32.116 5000");
        return false;
    }
    return true;
}
// 设置信号处理函数
void set_signal_handlers() {
    signal(SIGINT, catch_ctrl_c);
    signal(SIGTERM, catch_ctrl_c);
}
// 创建并运行ChatRoomClient
void create_and_run_client(const char* ip, int port) {
    crc_ptr = std::make_shared<ChatRoomClient>(ip, port);
    crc_ptr->Run();
}


//全局变量定义
std::vector<std::string> colors = {"\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m"};
std::string def_col = "\033[0m";

ChatRoomClient::ChatRoomClient(const char* ip, const int port): is_connected(false), m_ip(ip), m_port(port), exit_flag(false) {}

ChatRoomClient::~ChatRoomClient() {
    Close();
    if (thread_Input.joinable()) {
        thread_Input.join();
    }
}

void ChatRoomClient::Close() {
    if (is_connected) {
        tcp_client.Close();
        is_connected = false;
    }
    return;
}
// 连接服务端并开始读线程
bool ChatRoomClient::Connect() {
    // 如果有先关闭
    if (is_connected) {
        Close();
    }
    // 连接
    if (tcp_client.ConnectToServer(m_ip.c_str(), m_port) == false) {
        return false;
    }
    is_connected = true;
    return true;
}

//这里的菜单作为终端输出的菜单，这里不使用
void ChatRoomClient::Menu() {
    std::cout << "============== Welcome ChatRoom ==============" << std::endl;
    std::cout << "=====          0. Register               =====" << std::endl;
    std::cout << "=====          1. Login                  =====" << std::endl;
    std::cout << "=====          2. Exit                   =====" << std::endl;
    std::cout << "==============================================" << std::endl;
    return;
}

// 接收信息线程函数
void ChatRoomClient::RecvMessage() {
    while (1) {

        char message_buffer[1024];
        memset(message_buffer, 0, sizeof(message_buffer));

        if (tcp_client.Read(message_buffer) == false) {
            break;
        }
        if (exit_flag) break;

        int code = -1;
        LI::GetStrFromXML(message_buffer, "code", code); // 获取信息类型
        std::string message;
        std::string other_name;
        int other_color;
        shared_data::ShareData::server_choice=code;
        switch(code) {
            case 0: {
                    system("clear"); // 清屏
                    Menu();
                    std::cout << "Register Failed." << std::endl;  // 注册失败
                    return;
                    }
            case 1: {  // 注册成功
                    system("clear"); // 清屏
                    Menu();
                    std::cout << "Register Success." << std::endl; //注册成功
                    return;
                    }
            case 2: {
                    system("clear");
                    Menu();
                    std::cout << "Login Failed." << std::endl;  // 登录失败
                    return;
                    }
            case 3: {
                    std::cout << "Login Success." << std::endl;  // 登录成功
                    std::cout << "Select color(0 - 5): ";
                    //std::cin >> m_colorIndex;
                    //std::cout << "====== ChatRoom ======" << std::endl;
                    std::thread t(&ChatRoomClient::InputMessage, this);
                    thread_Input = std::move(t); // 创建输入线程
                    break;
                    }
            case 4: {
                    LI::GetStrFromXML(message_buffer, "message", message); // 收到信息
                    LI::GetStrFromXML(message_buffer, "name", other_name); //对方的姓名
                    LI::GetStrFromXML(message_buffer, "color", other_color);  //对方姓名颜色标识
                    EraseTextInTerminal(5);
                    //输出数据;
                    //这里不在终端输出，在可视化界面输出
                    std::cout << colors[other_color] << other_name << ": " << def_col << message << std::endl;
                    //共享值获得姓名，数据
                    shared_data::ShareData::server_other_name=other_name;
                    shared_data::ShareData::server_message=message;

                    std::cout << colors[m_colorIndex] << "You: " << def_col;
                    fflush(stdout);
                    break;
                    }
            default: return;
        }

    }

    Close();
    return;
}

// 发送信息线程函数
void ChatRoomClient::InputMessage() {

    // 确保关闭连接并释放资源
    Close();
    return;
    std::string message;
        //std::getline(std::cin, message); // 清空输入缓冲区
        while (1)
        {
            std::cout << colors[m_colorIndex] << "You: " << def_col;
            fflush(stdout);
            //std::getline(std::cin, message);
            message=shared_data::ShareData::client_message;
            if (message == "#exit") {
                exit_flag = true;
                // 形成格式
                std::string data("3"); // 退出登陆是 3 cmd
                LI::FormXML(data, "cmd");
                if (tcp_client.Write(data.c_str()) == false) {
                    break;
                };
                catch_ctrl_c(SIGINT);
            } // 输入 exit 退出

            // 形成格式
            LI::FormXML(message, "message");
            std::string data("2"); // 发信息是 2 cmd
            LI::FormXML(data, "cmd");
            data.append("<name>");
            data.append(m_Username);
            data.append("</name>");
            data.append("<color>");
            data.append(std::to_string(m_colorIndex));
            data.append("</color>");
            data.append(message);

            // 发送
            if (tcp_client.Write(data.c_str()) == false) {
                break;
            };
        }

        Close();
        return;
}
// 注册用户
//注册不使用这里的函数，使用QT中的注册函数;
//如果使用qt的注册函数，就会丧失server的功能，如果是在本地，可以使用qt注册函数，如果
//要远程访问数据库，就使用server访问
void ChatRoomClient::RegisterUser() {
    std::string message;
    // 输入信息
    //std::string getStr;
    //std::cout << "Create name: " ;
    //std::cin >> getStr;
    std::string regist_name=shared_data::ShareData::getShared_regist_name();
    message.assign(regist_name);
    message += " ";
    //std::cout << "Create password: " ;
    //std::cin >> getStr;
    std::string regist_password=shared_data::ShareData::getShared_regist_password();
    message.append(regist_password);
    //数据清除
    regist_name.clear();
    regist_password.clear();
    std::cout<<"注册成功";
    // 形成xml格式
    LI::FormXML(message, "message");
    // 添加 cmd label
    std::string data("0"); // 注册为 0 cmd
    LI::FormXML(data, "cmd");
    // 合成总的报文
    data.append(message);
    // 发送给客户端
    if (is_connected == false) {
        if(Connect() == false) {
            perror("connect.");
            return;
        }
    }
    if (tcp_client.Write(data.c_str()) == false) {
        perror("connect.");
        return;
    }

    return;
}
// 登录
void ChatRoomClient::Login() {
    std::string message;
    // 输入信息
    //std::string getStr;
    //std::cout << "Your name: " ;
    //std::cin >> getStr;
    std::string signing_name=shared_data::ShareData::getShared_signing_name();
    //m_Username = getStr; // 用户名
    message.assign(signing_name);
    message += " ";
    //std::cout << "Your password: " ;
    //std::cin >> getStr;
    std::string signing_password=shared_data::ShareData::getShared_signing_password();
    message.append(signing_password);

    // 形成xml格式
    LI::FormXML(message, "message");
    // 添加 cmd label
    std::string data("1"); // 登录为 1 cmd
    LI::FormXML(data, "cmd");
    // 合成总的报文
    data.append(message);
    // 发送给客户端
    if (is_connected == false) {
        if(Connect() == false) {
            perror("connect.");
            return;
        }
    }
    if (tcp_client.Write(data.c_str()) == false) {
        perror("Write.");
        return;
    }

    return;
}

void ChatRoomClient::Run() {

    system("clear");
    //Menu(); // 展示菜单

    while (1) {
        int choice = shared_data::ShareData::client_choice; //用一个共享值来决定
        //std::cout << "Your Choice: ";
        //std::cin >> choice;

        switch (choice) {
            case 0: {RegisterUser(); RecvMessage(); break;} //注册
            case 1: {Login(); RecvMessage(); break;} //登录

            case 2: {std::cout << "See you again." << std::endl; return;}

            default: {
                    std::cout << "Input error! Input again." << std::endl;
                    break;}
        }
    }
    return;
}

void ChatRoomClient::EraseTextInTerminal(int cnt) {
    char back_space = 8; //  backspace 字符
    for (int i = 0; i < cnt; ++i) {
        std::cout << back_space;
    }
}

void ChatRoomClient::Client_Run()
{
    // 设置信号处理函数
    set_signal_handlers();

    // 创建并运行ChatRoomClient
    create_and_run_client("127.0.0.1", 6000);   //直接固定端口号，不再更改
}
/*
int main(int argc, char const *argv[])
{
    //检查是否提供了两个命令行参数（除了程序名本身）
    if (argc != 3) {
        printf("No ip and port\nUsing example: ./client 192.168.32.116 5000");
        return -1;
    }
    这两行代码设置了信号处理函数。当程序接收到SIGINT（通常由用户按下Ctrl+C触发）
    或SIGTERM（通常是由系统或另一个进程发送的终止信号）时，会调用catch_ctrl_c函数。
    这意味着，当用户尝试通过Ctrl+C终止程序时，catch_ctrl_c函数会被调用，而不是直接终止程序。
    //signal(SIGINT, catch_ctrl_c);
    //signal(SIGTERM, catch_ctrl_c);
    // ChatRoomClient crc(argv[1], atoi(argv[2]));
    //这行代码使用std::make_shared来创建一个ChatRoomClient对象的智能指针
    //（std::shared_ptr）。该对象接受两个参数：
    //一个IP地址（从argv[1]获取）和一个端口号（从argv[2]转换而来）


   crc_ptr = std::make_shared<ChatRoomClient>(argv[1], atoi(argv[2]));

    crc_ptr->Run();


    return 0;

   //ChatRoomClient * client;
    // 检查命令行参数
    //if (!check_command_line_arguments(argc, argv)) {
    //    return -1;
    //}

    // 设置信号处理函数
    set_signal_handlers();

    // 创建并运行ChatRoomClient
    create_and_run_client("127.0.0.1", 6000);   //直接固定端口号，不再更改

    return 0;
}
*/
// 线程退出函数
void catch_ctrl_c(int sig) {
    crc_ptr->Close();
    crc_ptr->exit_flag = true;
    if (crc_ptr->thread_Input.joinable()) {
        crc_ptr->thread_Input.detach();
    }
    exit(sig);
}



