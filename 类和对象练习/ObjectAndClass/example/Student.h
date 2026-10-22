//
// Created by 24242 on 2026/10/20.
//

#ifndef OBJECTANDCLASS_STUDENT_H
#define OBJECTANDCLASS_STUDENT_H
#include <string>
#include <iostream>


class Student
{
private:
    const int d;
    std::string name;
    int age;
public:
    Student(const int d,std::string name,int age)
        :d(d),
        name(name),
        age(age)
    {}

    void setAge(int n)
    {
        if (n >= 0)
            age = n;
    }

    int getId() const;
    std::string getName() const;
    int getAge() const;
    void showMessage() const;
};


#endif //OBJECTANDCLASS_STUDENT_H