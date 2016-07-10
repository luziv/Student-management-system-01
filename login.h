#ifndef _LOGIN_H_
#define _LOGIN_H_

#include <map>

#define ACCOUNT_LEN 20
#define PASSWD_LEN 20

typedef std::map<std::string, std::string> LOGINMAP;
typedef LOGINMAP::iterator MAPIT;

class LoginClass{
public:
    LoginClass();
    ~LoginClass();

    int LoginInterface();
    int CreateAccount();
    int Login();
    int ModifyPwd();
private:
    LOGINMAP *account_map;

};
#endif
