#ifndef VECTOR_H
#define VECTOR_H


#include <cstddef>
#include <cmath>


class Vector{
    public:
        Vector(){};
        Vector(int x, int y);
        Vector operator+(const Vector& point);
        Vector operator-(const Vector& point);
        Vector operator*(double m);
        size_t operator*(const Vector& point);
        Vector operator/(double m);
        int GetX();
        int GetY();
        void SetX(int x);
        void SetY(int y);
        double Distance();
    private:
        int x_ = 0;
        int y_ = 0;
};


#endif //VECTOR_H
