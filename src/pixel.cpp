#include "pixel.h"

Pixel::Pixel(uint8_t blue, uint8_t green, uint8_t red): blue_(blue), green_(green), red_(red){}

void Pixel::SetValues(uint8_t blue, uint8_t green, uint8_t red){
    blue_ = blue;
    green_ = green;
    red_ = red;
}
