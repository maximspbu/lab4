#include "drawer.h"


Drawer::Drawer(size_t sizeX, size_t sizeY, const std::vector<std::vector<std::vector<Pixel>>>& digits):sizeX_(sizeX), sizeY_(sizeY), digits_(digits){
    for (size_t i = 0; i < sizeY_; ++i){
        canvas_.emplace_back();
        for (size_t j = 0; j < sizeX_; ++j){
            canvas_[i].emplace_back(255, 255, 255);
        }
    }
}

std::vector<std::vector<Pixel>> Drawer::GetCanvas(){
    return canvas_;
}

void Drawer::Circle(size_t x, size_t y, int radius){
    for (int i = -radius; i < radius + 1; ++i){
        for (int j = -radius; j < radius + 1; ++j){
            if (i*i + j*j <= radius*radius){
                canvas_[y + i][x + j] = {255, 0, 0};
                
            }
        }
    }
}

void Drawer::Line(size_t x0, size_t y0, size_t x1, size_t y1){
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xsign = dx > 0? 1: -1;
    int ysign = dy > 0? 1: -1;
    int xx, xy, yx, yy;
    dx = abs(dx);
    dy = abs(dy);
    if (dx>dy){
        xx = xsign;
        xy = 0;
        yx = 0;
        yy = ysign;
    } else {
        std::swap(dx, dy);
        xx = 0;
        xy = ysign;
        yx = xsign;
        yy = 0;
    }
    int d = 2*dy - dx;
    int y = 0;
    for (int x = 0; x < dx + 1; ++x){
        canvas_[y0 + x*xy + y*yy][x0 + x*xx + y*yx] = {0, 0, 0};
        if (d >= 0){
            y++;
            d -= 2*dx;
        }
        d += 2*dy;
    }
}

void Drawer::Num(size_t x, size_t y, size_t number){
    int step = log10(number);
    int remains;
    while (step > -1){
        remains = number/static_cast<int>(pow(10, step))%10;
        Digit(x, y, remains);
        step--;
        x += 10;
    }
}

void Drawer::Digit(size_t x, size_t y, size_t digit){
    for (size_t i = 0; i < digits_[digit].size(); ++i){
        for (size_t j = 0; j < digits_[digit][i].size(); ++j){
            if ((digits_[digit][i][j].blue_==255)&&(digits_[digit][i][j].green_==255)&&(digits_[digit][i][j].red_==255)){
                continue;
            }
            canvas_[y+i][x+j] = {digits_[digit][i][j].blue_, digits_[digit][i][j].green_, digits_[digit][i][j].red_}; //digits_[digit][i][j].blue_, digits_[digit][i][j].green_, digits_[digit][i][j].red_
        }
    }
}
