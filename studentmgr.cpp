
#include <iostream>

#include <cstdlib>

#include "studentmgr.h"
#include "tool.h"

#define DATA_FILE_NAME "student_data.txt"

using namespace std;

StudentMgr::StudentMgr()
{
    list = new StudentList;
    list->pHead = NULL;
    list->pEnd  = NULL;
    list->len   = 0;

    in.open(DATA_FILE_NAME);
    if (in) {
        while(!in.eof()) {
            Student * stu = new Student;
            stu->InputEx(in);
            if (0 == stu->GetNumber()) {
                delete stu;
                break;
            }
            stu->next = NULL;
            if (list->pHead == NULL) {
                list->pHead = stu;
                list->pEnd = stu;
            } else {
                list->pEnd->next = stu;
                list->pEnd = stu;
            }
            (list->len)++;
        }
    }
    in.close();
}

StudentMgr::~StudentMgr()
{
    //std::cout << "come here:" << list->len << std::endl;
    out.open(DATA_FILE_NAME);
    Student * p = list->pHead;
    while (p) {
        p->Output(out); 
        Student * tmp = p->next;
        delete p;
        p = tmp;
    }

    out.close();
    delete list;
}


bool StudentMgr::MainMenu()
{
    cout << "----------------------------------------------" << endl;
    cout << "------------ 学生信息管理系统 ----------------" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "------------ 1.显示学生成绩   ----------------" << endl;
    cout << "------------ 2.增加学生成绩   ----------------" << endl;
    cout << "------------ 3.删除学生成绩   ----------------" << endl;
    cout << "------------ 4.修改学生成绩   ----------------" << endl;
    cout << "------------ 5.查找学生成绩   ----------------" << endl;
    cout << "------------ 6.退出系统       ----------------" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "----------------------------------------------" << endl;

    int opt;
    cout << "你要做什么:";
    cin >> opt;
    switch(opt) {
        case 1 : 
            return ShowScore();
        case 2 :
            return AddStudent();
        case 3 :
            return DelStudent();
        case 4 :
            return ModifyScore();
        case 5 :
            return FindStudent();
        case 6 :
            return true;
        default:
            cout << "error opt." << endl;
            return false;
    }
    return true;
}

bool StudentMgr::ShowScore()
{
    PrintLine("显示学生成绩");
    cout << "学号" << " 姓名" << " 语文" << " 数学" << " 英语" << endl;
    Student * p = list->pHead;
    while (p) {
        p->ShowEx();
        p = p->next;
    }
    return false;
}

bool StudentMgr::DelStudent()
{
    PrintLine("删除学生成绩");
    int num;
    cout << "该学生学号:"; 
    cin >> num;
    Student * p = list->pHead;
    Student * tmp = NULL;
    if (p == NULL)
        return false;

    if (p->GetNumber() == num) {
        list->pHead = p->next; 
        list->len--;
        delete p;
    } else {
        do {
            tmp = p->next;
            if (tmp->GetNumber() == num) {
                if (tmp == list->pEnd){
                    list->pEnd = p;
                }
                p->next = tmp->next;
                list->len--;
                delete tmp;
                break;
            } else {
                p = p->next; 
            }
        } while(p);
    }
    return false;
}

bool StudentMgr::ModifyScore()
{
    cout << "修改学生成绩" << endl;
    cout << "学号:";
    int num;
    cin >> num;
    Student* p = list->pHead;
    while (p) {
        if (p->GetNumber() == num) {
            p->ShowEx(); 
            p->Modify();
            break;
        } 
        p = p->next; 
    }
    return false;
}

bool StudentMgr::FindStudent()
{
    cout << "查找学生成绩" << endl;
    cout << "学号:";
    int num;
    cin >> num;
    Student * p = list->pHead;
    while (p) {
        if (p->GetNumber() == num) {
            p->ShowEx(); 
            break;
        }
        p = p->next; 
    }
    PrintNotice("没有该学生");
    return false;
}

bool StudentMgr::AddStudent()
{
    cout << "增加学生成绩" << endl;
    Student * stu = new Student;
    stu->Input();
    stu->next = NULL;

    if (list->pHead == NULL) {
        list->pHead = stu;
        list->pEnd = stu;
    } else {
        Student * p = list->pHead;
        while (p) {
            if (p->GetNumber() == stu->GetNumber()) {
                PrintNotice("该学生已录入.");
                return false;
            }
            p = p->next;
        }
        list->pEnd->next = stu;
        list->pEnd = stu;
    }
    list->len++;
    return false;
}

