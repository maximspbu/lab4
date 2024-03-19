#include "point.h"

Point::Point():x_(0), y_(0){}

Point::Point(int x, int y): x_(x), y_(y){}

int Point::GetX(){
    return x_;
}

int Point::GetY(){
    return y_;
}

void Point::SetX(int x){
    x_ = x;
}

void Point::SetY(int y){
    y_ = y;
}

Point Point::operator+(Vector vector){
    return Point(x_+vector.GetX(), y_+vector.GetY());
}

Vector Point::operator-(Point& point){
    return Vector(x_-point.GetX(), y_-point.GetY());
}
