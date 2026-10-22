//
// Created by 24242 on 2026/10/21.
//

#include "Point.h"

bool Point::operator==(const Point& other) const
{
    return (this->x == other.x && this->y == other.y);
}
