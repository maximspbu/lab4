#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>

struct Pixel{
    Pixel(uint8_t blue, uint8_t green, uint8_t red);
    void SetValues(uint8_t blue, uint8_t green, uint8_t red);
    uint8_t blue_ = 255;
    uint8_t green_ = 255;
    uint8_t red_ = 255;
};

#endif //PIXEL_H
