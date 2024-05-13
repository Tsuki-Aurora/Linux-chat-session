#ifndef SHAREDATA_H
#define SHAREDATA_H
#include <string>
namespace shared_data {
class ShareData {
public:
    // 声明静态公有成员变量
    static std::string regist_name;
    static std::string regist_password;

    static std::string signin_name;
    static std::string signin_password;
    //用来获取server端的数据
    static std::string server_message;
    //用来存放发送的数据
    static std::string client_message;
    //用来存放server返回的姓名
    static std::string server_other_name;

    //设置client动态变量
    static int client_choice;
    //设置server动态量
    static int server_choice;

    // 如果需要，可以添加静态公有函数来操作这个值
    // 静态公有函数来设置值
    static void setSharedValue(const std::string& usernames, const std::string& password);

    static std::string getShared_regist_name(); //get方法，得到regist_name
    static std::string getShared_regist_password(); //get方法，得到regist_password
    static std::string getShared_signing_name();//get方法，得到signing_name
    static std::string getShared_signing_password();//get方法，得到signing_password
    static int get_client_choice();
    static int get_server_choice();
};
}

#endif // SHARED_DATA_H

