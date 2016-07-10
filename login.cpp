#include <iostream>
#include <fstream>

#include <cstring>
#include <cstdlib>

#include "login.h"
#include "tool.h"

using std::cout;
using std::endl;
using std::cin;
using std::ios;

#define ACCOUNT_DATA_FILE_NAME "account_data.txt"

LoginClass::LoginClass()
{
    account_map = new LOGINMAP;
    FILE *fp;
    fp = fopen(ACCOUNT_DATA_FILE_NAME, "r");
    if (fp != NULL) {
        char tmpAccount[ACCOUNT_LEN];
        char tmpPwd[PASSWD_LEN];
        while(2==fscanf(fp, "%s%s", tmpAccount, tmpPwd)) {
            //cout << tmpAccount << ' ' << tmpPwd << endl;
            //account_map[tmpAccount] = tmpPwd;
            account_map->insert(make_pair(tmpAccount, tmpPwd));
        }
    } else {
        PrintNotice("打开文件失败"); 
    }
    fclose(fp);
}

LoginClass::~LoginClass()
{
    FILE *fp;
    fp = fopen(ACCOUNT_DATA_FILE_NAME, "w");
    if (fp != NULL) {
        for (MAPIT it=account_map->begin(); it!=account_map->end(); ++it) {
            //cout << "key:" << it->first.c_str() << " account:" << it->second.c_str() << endl;
            fprintf(fp, "%s %s\n", it->first.c_str(), it->second.c_str()); //转成c风格的字符串
        } 
        delete account_map;
    } else {
        PrintNotice("打开文件失败"); 
    }
    fclose(fp);
}

int LoginClass::LoginInterface()
{
    PrintLine("登录");
    cout << "1.注册帐号" << endl;
    cout << "2.登录" << endl;
    cout << "3.修改密码" << endl;
    cout << "4.安全退出" << endl;

    int login_result = 0;
    int opt;
    cout << "你要做什么:";
    cin >> opt;
    switch (opt) {
        case 1 :
            login_result = CreateAccount();
            break;
        case 2 :
            login_result = Login();
            break;
        case 3 :
            login_result = ModifyPwd();
            break;
        case 4 :
            login_result = 3;
            break;
        default:
            cout << "error opt" << endl;
            login_result = 2;
            break;
    }
    return login_result;
}

int LoginClass::CreateAccount()
{
    PrintLine("注册");

    char account[ACCOUNT_LEN];
    char pwd[PASSWD_LEN] = {'\0'};
    char tmp[PASSWD_LEN] = {'\0'};

    cout << "新帐号:";
    cin >> account;
    getchar();
    //cin.sync();

    //TODO: 帐号合法性验证

    // 帐号唯一性验证
    MAPIT it = account_map->find(account);
    if (it != account_map->end()) {
        PrintNotice("帐号已存在");
        return 2;
    }

    cout << "密码:";
    EnterPassword(pwd);
    //TODO: 密码合法性验证
    cout << "请再输入密码:";
    EnterPassword(tmp);

    if (0 == strlen(pwd)) {
        PrintNotice("密码不能空"); 
        return 2;
    }
    cout << "pwd:" << pwd << endl;
    cout << "tmp:" << tmp << endl;
    if (0 != strcmp(pwd, tmp)) {
        PrintNotice("两次密码不一致");
        return 2;
    }

    account_map->insert(make_pair(account, pwd));

    PrintNotice("注册成功");
    return 1;
}

int LoginClass::Login()
{
    PrintLine("登录");
    char account[ACCOUNT_LEN];
    char tmpAccount[ACCOUNT_LEN];

    char pwd[PASSWD_LEN];
    char tmpPwd[PASSWD_LEN];

    cout << "帐号:";
    cin >> account;
    getchar();

    MAPIT it = account_map->find(account);
    if (it == account_map->end()) {
        PrintNotice("帐号不存在");
        return 2;
    }

    cout << "密码:";
    EnterPassword(pwd);

    if (0!=strcmp(it->second.c_str(), pwd)) {
        PrintNotice("密码错误");
        return 22;
    }

    PrintNotice("登录成功");
    return 1;
}

int LoginClass::ModifyPwd()
{
    PrintLine("修改密码");

    char account[ACCOUNT_LEN];
    char tmpAccount[ACCOUNT_LEN];

    char pwd[PASSWD_LEN];
    char tmpPwd[PASSWD_LEN];

    cout << "帐号:";
    cin >> account;
    MAPIT it = account_map->find(account);
    if (it == account_map->end()) {
        PrintNotice("帐号不存在");
        return 2;
    }

    cout << "原密码:";
    cin >> pwd;
    if (0!=strcmp(it->second.c_str(), pwd)) {
        PrintNotice("密码错误"); 
        return 2;
    }

    cout << "新密码:";
    cin >> pwd;
    cout << "确认新密码:";
    cin >> tmpPwd;
    if (0!=strcmp(pwd, tmpPwd)) {
        PrintNotice("密码不一致");
        return 2;
    }
    it->second = pwd;
    PrintNotice("修改成功");
    return 0;
}

