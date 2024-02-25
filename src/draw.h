#ifndef DRAW_H
#define DRAW_H
#include <vector>
#include <cstddef>

class Draw{
    private:
        size_t sizeX, sizeY;
        std::vector<std::vector<size_t>> canvas;
    public:
        Draw(size_t sizeX_, size_t sizeY_);
        void circle(size_t coordX, size_t coordY, size_t radius);
        void line(size_t coordX1, size_t coordY1, size_t coordX2, size_t coordY2);
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
        
};

#endif //DRAW_H
