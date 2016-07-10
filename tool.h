
#ifndef _TOOL_H_
#define _TOOL_H_

using namespace std;

//打印神秘分割线
void PrintLine(string str);

//打印提示
void PrintNotice(string str);

int set_disp_mode(int fd,int option);

int getch(void);

int EnterPassword(char *pwd);

#endif //_TOOL_H_

