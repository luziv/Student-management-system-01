#ifndef _STUDENTMGR_H_
#define _STUDENTMGR_H_ 

#include <fstream>

#include "student.h"

typedef struct {
    Student *pHead;
    Student *pEnd;
    int len;
}StudentList;

class StudentMgr{
public:
    StudentMgr();
    ~StudentMgr();


    bool MainMenu();
    bool ShowScore();
    bool AddStudent();
    bool DelStudent();
    bool ModifyScore();
    bool FindStudent();
private:
    StudentList * list;

    std::ifstream in;
    std::ofstream out;
};

#endif
