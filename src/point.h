#ifndef POINT_H
#define POINT_H

#include "vector.h"

struct Point{
    Point();
    Point(int x, int y);
    Point operator+(Vector vector);
    Vector operator-(Point& vector);
    int GetX();
    int GetY();
    void SetX(int x);
    void SetY(int y);
    int x_, y_;
};

#endif //POINT_H