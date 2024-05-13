#ifndef CHATROOMCLIENT_H // 如果CHATROOMCLIENT_H没有被定义
#define CHATROOMCLIENT_H // 定义CHATROOMCLIENT_H
#include "cppNetWork.h"
#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include <signal.h>
//得到共享值
#include"ShareData.h"


// 字体颜色
// 红 绿 黄 蓝 紫 青
//头文件中声明,源文件中定义
extern std::vector<std::string> colors;
extern std::string def_col;
/*文件中声明了一个全局变量（或数组），
并且没有使用 extern 关键字来指明这是一个在其他地方定义的变量。
当这个头文件被多个源文件包含时，每个源文件都会尝试定义这个变量。*/


void catch_ctrl_c(int sig);

class ChatRoomClient {
public:
    friend void catch_ctrl_c(int sig);

    //定义注册，登陆的公共变量
    std::string regist_name; //注册姓名
    std::string regist_password; //注册密码
    std::string signin_name; //登录姓名
    std::string signin_password; //登录密码

    LI::TcpClient tcp_client;    // 客户端对象
    bool is_connected;           // 连接标记
    const std::string m_ip;      // 服务端 ip 地址
    const int m_port;            // 服务端端口号
    std::thread thread_Input;    // 键入信息线程
    bool exit_flag;              // 退出标记
    std::string m_Username;      // 用户名
    int m_colorIndex;            // 字体颜色

    ChatRoomClient(const char* ip, const int port);
    // 接收信息
    void RecvMessage();
    // 输入要发送的信息
    void InputMessage();
    // 注册用户
    void RegisterUser();
    // 用户登陆
    void Login();
    // 连接客户端
    bool Connect();
    // 菜单
    void Menu();
    // 关闭连接
    void Close();
    // 运行接口
    void Run();
    // 删除输出的字符
    void EraseTextInTerminal(int cnt);

    //client_run
    void Client_Run();

    ~ChatRoomClient();
};
#endif // 结束包含保护
