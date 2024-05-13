#ifndef CHATROOMSERVER_H
#define CHATROOMSERVER_H
#include "ThreadPool.hpp"
#include "cppNetWork.h"
#include <iostream>
#include <sys/epoll.h>
#include <set>
#include <sstream>
#include <signal.h>
#include <mysql/mysql.h>

// ---------------------- 用户信息文件类 ---------------------------

// 用户信息 sql 类
class UserSQL {
private:
    MYSQL mysql_conn;  // 数据库连接对象
    MYSQL* mysql_h;    // 连接句柄
    MYSQL_RES* result; // 查询结果
    bool is_connect;   // 连接标记
public:
    
    UserSQL();

    ~UserSQL();

    void Close();

    /// @brief 连接数据库
    /// @param user 连接数据库的用户名
    /// @param password 用户名对应的密码
    /// @param database 连接的数据库名
    /// @return 是否连接成功
    bool Connect(const std::string& user = "root", const std::string& password = "083911Aa", const std::string& database = "account_information");

    /// @brief 查找用户名
    /// @param name 待查找的用户名
    /// @return 若用户名存在则返回密码, 不存在返回空字符串
    std::string SearchUser(const char* name);
    
    /// @brief 增加用户
    /// @param name 待增加的用户名
    /// @param password 待增加的密码
    /// @return true-成功, false-失败
    bool AddUser(const char* name, const char* password);
};

// ---------------------- /用户信息文件类 ---------------------------

void Catch_ctrl_c(int sig);

class ChatRoomServer {
private:
    LI::LogFile logfile;         // 日志文件
    LI::TcpServer tcp_server;    // 服务端对象
    LI::ThreadPool thread_pool;  // 线程池对象
    const size_t MAXENENTS;      // epoll一次能返回的最大的事件数
    std::set<int> set_connfd;    // 已连接的 connfd 容器
    int epollfd;                 // epollfd
    // 锁
    std::mutex set_lock;
    
public:
    friend void Catch_ctrl_c(int sig);

    ChatRoomServer(const size_t threads = 5 ,const size_t maxenents = 10);
    // 初始化服务端
    bool InitServer(const char* ip, const unsigned int port);
    // 初始化日志文件
    bool InitLogFile(const char* filename, std::ios::openmode openmode = std::ios::app, bool bBackup = true, bool bEnbuffer = false, const size_t MaxLogSize = 100);

    void runServer();

    ~ChatRoomServer();

private:
    // 接收并广播信息
    void broadcastMessage(const std::string& name, const std::string& str, int colorIndex, int sockfd);
    // 注册操作
    void Register(const std::string& str, int sockfd);
    // 登陆操作
    void LogIN(const std::string& str, int sockfd);
    // 退出登陆操作
    void LogOUT(int sockfd);
};
#endif
