#include <iostream>

#include "login.h"
#include "studentmgr.h"

int main()
{
    int login_result = 0; // 0:未登录 1:登录成功 2:登录失败 3:退出系统
    LoginClass login;
    while(login_result == 0) {
        //登录
        login_result = login.LoginInterface();
    }

    bool isExit = false;
    StudentMgr studentMgr;
    while(!isExit && login_result == 1) {
        //进入系统
        isExit = studentMgr.MainMenu();
    }
    
    std::cout << "再见!" << std::endl;
}

