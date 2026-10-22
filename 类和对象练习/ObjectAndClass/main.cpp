#include "example/Student.h"
#include "example/Point.h"
#include "example/Tracker.h"
#include "example/Score.h"

#include <iostream>

void StudentTest()
{
    Student s1(1,"XiaoMing",18);
    s1.showMessage();
    const Student s2(2,"XiaoHong",19);
    s2.showMessage();
}

void PointTest()
{
    Point p1;
    Point p2(2,3);
    Point p3(2,3);
    Point p4(3,2);
    if (p1 == (0,0))
    {

        std::cout << "Equal" << std::endl;
    }else
    {
        std::cout << "Different" << std::endl;
    }
    if (p2 == p3)
    {
        std::cout << "Equal" << std::endl;
    }else
    {
        std::cout << "Different" << std::endl;
    }
    if (p3 == p4)
    {
        std::cout << "Equal" << std::endl;
    }else
    {
        std::cout << "Different" << std::endl;
    }
}

void TrackerTest()
{
    std::cout << Tracker::getLiveCount() << std::endl;
    Tracker a;
    std::cout << Tracker::getLiveCount() << std::endl;
    {
        Tracker b;
        Tracker c;
        std::cout << Tracker::getLiveCount() << std::endl;
    }
    std::cout << Tracker::getLiveCount() << std::endl;
}

void ScoreTest()
{
        Score a(80);
        Score b(a);
        std::cout << "a: " << a.getValue() <<" " << "b: " << b.getValue() << std::endl;
        b.setValue(90);
        std::cout << "b: " << b.getValue() << std::endl;
        Score c = a;
        std::cout << "c " << c.getValue() << std::endl;

        a = b = c;
        std::cout << "a: " << a.getValue() <<" " << "b: " << b.getValue() <<  " " << "c: " << c.getValue() <<std::endl;
        a = a;
        std::cout << "a: " << a.getValue() << std::endl;
}

int main() {
    StudentTest();

    PointTest();

    TrackerTest();

    StudentTest();

    return 0;
}
