#ifndef VECTOR_H
#define VECTOR_H


#include <cstddef>
#include <cmath>


class Vector{
    public:
        Vector(){};
        Vector(double x, double y);
        Vector operator+(const Vector& point);
        Vector operator-(const Vector& v1);
        Vector operator*(double m);
        size_t operator*(const Vector& point);
        Vector operator/(double m);
        double GetX();
        double GetY();
        void SetX(double x);
        void SetY(double y);
        double Distance();
    private:
        double x_;
        double y_;
};


#endif //VECTOR_H
