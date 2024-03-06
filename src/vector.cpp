#include "vector.h"


Vector::Vector(double x, double y): x_(x), y_(y){};

Vector Vector::operator+(const Vector& v1){
    return Vector(x_+v1.x_, y_+v1.y_);
}

Vector Vector::operator-(const Vector& v1){
    return Vector(x_-v1.x_, y_-v1.y_);
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
    return sqrt(x_ * x_ + y_ * y_);
}

double Vector::GetX(){
    return x_;
}

double Vector::GetY(){
    return y_;
}

void Vector::SetX(double x){
    x_=x;
}

void Vector::SetY(double y){
    y_=y;
}
