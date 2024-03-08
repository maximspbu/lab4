#ifndef DRAWER_H
#define DRAWER_H


#include "pixel.h"

#include <vector>
#include <cstddef>
#include <cmath>
#include <iostream>


class Drawer{
    public:
        Drawer(size_t sizeX_, size_t sizeY_);
        std::vector<std::vector<Pixel>> GetCanvas();
        void circle(size_t coordX, size_t coordY, int radius);
        void line(int coordX1, int coordY1, int coordX2, int coordY2);
        void zero(size_t coordX, size_t coordY);
        void one(size_t coordX, size_t coordY);
        void two(size_t coordX, size_t coordY);
        void three(size_t coordX, size_t coordY);
        void four(size_t coordX, size_t coordY);
        void five(size_t coordX, size_t coordY);
        void six(size_t coordX, size_t coordY);
        void seven(size_t coordX, size_t coordY);
        void eight(size_t coordX, size_t coordY);
        void nine(size_t coordX, size_t coordY);
    private:
        size_t sizeX, sizeY;
        std::vector<std::vector<Pixel>> canvas;
};


#endif //DRAWER_H
