#include "vector.h"


Vector::Vector(int x, int y): x_(x), y_(y){};

Vector Vector::operator+(const Vector& point){
    return Vector(x_ + point.x_, y_ + point.y_);
}

Vector Vector::operator-(const Vector& point){
    return Vector(x_ - point.x_, y_ - point.y_);
}

Vector Vector::operator*(double m){
    return Vector(x_ * m, y_ * m);
}

size_t Vector::operator*(const Vector& point){
    return x_ * point.x_ + y_ * point.y_;
}

Vector Vector::operator/(double m){
    return Vector(x_ / m, y_ / m);
}

double Vector::Distance(){
    return pow(x_ * x_ + y_ * y_, 0.5);
}

int Vector::GetX(){
    return x_;
}

int Vector::GetY(){
    return y_;
}

void Vector::SetX(int x){
    x_=x;
}

void Vector::SetY(int y){
    y_=y;
}
