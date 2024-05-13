#include "ShareData.h"

// 静态成员变量
namespace shared_data {
    //注册
    std::string ShareData::regist_name;
    std::string ShareData::regist_password;
    //登录
    std::string ShareData::signin_name ;
    std::string ShareData::signin_password;
    //数据
    std::string ShareData::server_message;
    std::string ShareData::client_message;
    //std::string ShareData::client_choice;
    std::string ShareData::server_other_name;

    int ShareData::client_choice;
    int ShareData::server_choice;
    //server
    //int ShareData::server_open_judgment=0;


    // 登录静态成员函数的定义
    void ShareData::setSharedValue(const std::string& usernames, const std::string& password) {
        signin_name = usernames; //登录姓名
        signin_password= password; //登录密码
    }
    //定义get方法
    std::string ShareData::getShared_regist_name() {
        return regist_name;
    }
    std::string ShareData::getShared_regist_password(){
        return regist_password;
    }
    std::string ShareData::getShared_signing_name() {
        return signin_name;
    }
    std::string ShareData::getShared_signing_password() {
        return signin_password;
    }
    int ShareData::get_client_choice()
    {
        return client_choice;
    }
    int ShareData::get_server_choice()
    {
        return server_choice;
    }
}
