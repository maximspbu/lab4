#include "draw.h"

Draw::Draw(size_t sizeX_, size_t sizeY_):sizeX(sizeX_), sizeY(sizeY_){
    canvas.resize(sizeY);
    for (size_t i = 0; i < sizeX; i++) canvas[i].resize(sizeX);
}
