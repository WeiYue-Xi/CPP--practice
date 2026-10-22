//
// Created by 24242 on 2026/10/20.
//

#include "Student.h"
#include <iostream>

int Student::getId() const
{
    return d;
}

std::string Student::getName() const
{
    return name;
}

int Student::getAge() const
{
    return age;
}

void Student::showMessage() const
{
    std::cout << "学号：" << d <<" " << "姓名：" << " " << name << " " << "年龄：" << age << std::endl;
}
