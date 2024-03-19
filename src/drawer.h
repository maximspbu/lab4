#ifndef DRAWER_H
#define DRAWER_H


#include "pixel.h"

#include <vector>
#include <cstddef>
#include <cmath>
#include <iostream>
#include <fstream>


class Drawer{
    public:
        Drawer(size_t sizeX_, size_t sizeY_, const std::vector<std::vector<std::vector<Pixel>>>& digits);
        std::vector<std::vector<Pixel>> GetCanvas();
        void Circle(size_t x, size_t y, int radius);
        void Line(size_t x0, size_t y0, size_t x1, size_t y1);
        void Num(size_t x, size_t y, size_t number);
        void Digit(size_t x, size_t y, size_t digit);
    private:
        size_t sizeX_, sizeY_;
        std::vector<std::vector<Pixel>> canvas_;
        std::ifstream file_;
        std::vector<std::vector<std::vector<Pixel>>> digits_;
};


#endif //DRAWER_H
