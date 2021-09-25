//
// Created by echo-djx on 2021/9/25.
//
#include <iostream>
#include <string>
#include "user.pb.h"

/*
 * userservice原来为应该本地服务，提供了两个进程内的本地方法，Login和GetFriendLists
 */


class UserService : public fixbug::UserServiceRPC {
public:
    bool Login(std::string name, std::string pwd) {
        std::cout << "doing local service:Login" << std::endl;
        std::cout << " name " << name << " pwd:" << pwd << std::endl;
    }

    /*
   重写基类UserServiceRpc的虚函数 框架直接调用下面这些方法
   1. caller   ===>   Login(LoginRequest)  => 网络传输 =>   callee
   2. callee   ===>    Login(LoginRequest)  => 交到下面重写的Login方法上
   */
    void Login(::google::protobuf::RpcController *controller,
               const ::fixbug::LoginRequest *request,
               ::fixbug::LoginResponse *response,
               ::google::protobuf::Closure *done) {
        // 框架给业务上报了请求参数LoginRequest，应用获取相应数据做本地业务
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 本地业务执行
        bool login_result = Login(name, pwd);

        // 把响应写入  包括错误码、错误消息、返回值
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_sucess(login_result);

        // 执行回调操作   执行响应对象数据的序列化和网络发送（都由框架来完成）
        done->Run();
    }
};

int main(int argc, char **argv) {
    //调用框架的初始化操作

    //把UserService对象发布到rpc节点上

    //启动一个rpc服务发布节点

    return 0;
}