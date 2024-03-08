#include "drawer.h"


Drawer::Drawer(size_t sizeX_, size_t sizeY_):sizeX(sizeX_), sizeY(sizeY_){
    for (size_t i = 0; i < sizeY_; ++i){
        canvas.emplace_back();
        for (size_t j = 0; j < sizeX_; ++j){
            canvas[i].emplace_back(255, 255, 255);
        }
    }
}

std::vector<std::vector<Pixel>> Drawer::GetCanvas(){
    return canvas;
}

void Drawer::circle(size_t coordX, size_t coordY, int radius){
    //std::cout << "flag\n";
    for (int i = -radius; i < radius + 1; ++i){
        for (int j = -radius; j < radius + 1; ++j){
            //
            if (i*i + j*j <= radius*radius){
                canvas[coordY+i][coordX+j].SetValues(255, 0, 0);
                
            }
        }
    }
}

void Drawer::line(int x0, int y0, int x1, int y1){
    int dx = x1-x0;
    int dy = y1-y0;
    int xsign = dx>0?1:-1;
    int ysign = dy>0?1:-1;
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
    int d = 2*dy-dx;
    int y = 0;
    for (int x = 0; x < dx+1; ++x){
        canvas[y0+x*xy+y*yy][x0+x*xx+y*yx].SetValues(0,0,0);
        if (d>=0){
            y+=1;
            d -= 2*dx;
        }
        d += 2*dy;
    }
}

void Drawer::zero(size_t coordX, size_t coordY){

}

void Drawer::one(size_t coordX, size_t coordY){
    
}

void Drawer::two(size_t coordX, size_t coordY){
    
}

void Drawer::three(size_t coordX, size_t coordY){
    
}

void Drawer::four(size_t coordX, size_t coordY){
    
}

void Drawer::five(size_t coordX, size_t coordY){
    
}

void Drawer::six(size_t coordX, size_t coordY){
    
}

void Drawer::seven(size_t coordX, size_t coordY){
    
}

void Drawer::eight(size_t coordX, size_t coordY){
    
}

void Drawer::nine(size_t coordX, size_t coordY){
    
}
