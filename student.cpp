#include <iostream>
#include "student.h"

using namespace std;

void Student::Show()
{
    cout << "----------------" << endl;
    cout << "姓名:" << name    << endl;
    cout << "学号:" << number  << endl;
    cout << "语文:" << chinese << endl;
    cout << "数学:" << math    << endl;
    cout << "英语:" << english << endl;
    cout << "----------------" << endl;
}

void Student::ShowEx()
{
    cout << number << " " << name << " " << chinese << " " << math << " " << english << endl;
}

void Student::Input()
{
    cout << "请输入你的成绩:" << endl;
    cout << "学号:";
    cin >> number;

    cout << "姓名:";
    cin >> name;

    cout << "语文:";
    cin >> chinese;

    cout << "数学:";
    cin >> math;

    cout << "英语:";
    cin >> english;
}

void Student::Modify()
{
    cout << "请重新输入成绩:" << endl;

    cout << "语文:";
    cin >> chinese;

    cout << "数学:";
    cin >> math;

    cout << "英语:";
    cin >> english;

}

void Student::InputEx(std::ifstream & in)
{
    in >> number >> name >> chinese >> math >> english;
}

void Student::Output(std::ofstream & out)
{
    out << number << ' ' << name << ' ' << chinese << ' ' << math << ' ' << english << '\n'; 
}


char * Student::GetName()
{
    return name;
}

int Student::GetNumber()
{
    return number;
}



