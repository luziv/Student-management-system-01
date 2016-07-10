
#include <iostream>
#include <string>
#include <stdio.h>
#include <termios.h> 
#include <errno.h>
#include <unistd.h>

#include "login.h"
#include "tool.h"

using namespace std;

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
#define ALARM 7
#define BACKSPACE 8

//打印神秘分割线
void PrintLine(string str)
{
    cout << "--------------------------" << endl;
    cout << "--------神秘分割线--------" << endl;
    cout << "--------------------------" << endl;
    cout << "★ ★ ★ ★ ★  " << str << " ★ ★ ★ ★ ★ "<< endl;
}

//打印提示
void PrintNotice(string str)
{
    cout << "★ 提示★ : " << str << endl;
}

int set_disp_mode(int fd,int option)  
{  
   int err;  
   struct termios term;  
   if(tcgetattr(fd,&term)==-1){  
     perror("Cannot get the attribution of the terminal");  
     return 1;  
   }  
   if(option)  
        term.c_lflag|=ECHOFLAGS;  
   else  
        term.c_lflag &=~ECHOFLAGS;  
   err=tcsetattr(fd,TCSAFLUSH,&term);  
   if(err==-1 && err==EINTR){  
        perror("Cannot set the attribution of the terminal");  
        return 1;  
   }  
   return 0;  
}

int getch(void)
{    
    struct termios tm, tm_old;
    int fd = STDIN_FILENO, c;
    if(tcgetattr(fd, &tm) < 0)
            return -1;
    tm_old = tm;
    cfmakeraw(&tm);
    if(tcsetattr(fd, TCSANOW, &tm) < 0)
            return -1;
    //c = fgetc(stdin);
    c = getchar();
    if(tcsetattr(fd, TCSANOW, &tm_old) < 0)
            return -1; 
    return c;
}    

int EnterPassword(char *pwd)
{
    int ch;
    int j = 0;
    for (int i=0; i<PASSWD_LEN; ++i) {
        ch = getch(); 

        if (ch == BACKSPACE) {        // 删除键处理 TODO
//            if(i==0)
//            {
//                putchar(ALARM);
//                continue;
//            }
//            i--;
//            putchar(BACKSPACE);
//            putchar(' ');
//            putchar(BACKSPACE);
        } else {
            if (ch == '\n' || ch == '\r') {
                putchar('\n');
                break;
            }
            pwd[j] = ch;
            j++;
            putchar('*');
        }
    }
    return 0;
}

