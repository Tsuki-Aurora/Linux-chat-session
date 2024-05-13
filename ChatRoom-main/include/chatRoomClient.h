#ifndef CHATROOMCLIENT_H
#define  CHATROOMCLIENT_H
#include "cppNetWork.h"
#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include <signal.h>

// 字体颜色
// 红 绿 黄 蓝 紫 青
std::vector<std::string> colors = {"\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m"};
std::string def_col = "\033[0m";

void catch_ctrl_c(int sig);

class ChatRoomClient {
public:
    friend void catch_ctrl_c(int sig);

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

    ~ChatRoomClient();
};
#endif

