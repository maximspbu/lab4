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
        void Circle(int coordX, int coordY, int radius);
        void Line(int coordX1, int coordY1, int coordX2, int coordY2);
        void Num(int x, int y, int number);
        void Digit(int x, int y, int digit);
    private:
        size_t sizeX_, sizeY_;
        std::vector<std::vector<Pixel>> canvas_;
        std::ifstream file_;
        std::vector<std::vector<std::vector<Pixel>>> digits_;
};


#endif //DRAWER_H
