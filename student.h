#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <fstream>

#define NAME_LEN 20

class Student{

public:
    void Show();
    void ShowEx();
    void Input();       //(由cin获取)
    void Modify();
    void InputEx(std::ifstream&);     //(从文件中读取)
    void Output(std::ofstream&);      //(写入文件)

    char* GetName();
    int GetNumber();

private:
    char name[NAME_LEN];
    int number;
    int english;
    int chinese;
    int math;

public:
    Student * next;
};

#endif

