//
// Created by 24242 on 2026/10/21.
//

#ifndef OBJECTANDCLASS_POINT_H
#define OBJECTANDCLASS_POINT_H


class Point
{
private:
    int x;
    int y;
public:
    Point(int x = 0,int y = 0)
        :x(x),y(y)
    {
    }
    bool operator==(const Point& other) const;
};


#endif //OBJECTANDCLASS_POINT_H