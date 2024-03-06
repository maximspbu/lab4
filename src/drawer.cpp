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

void Drawer::line(size_t coordX1, size_t coordY1, size_t coordX2, size_t coordY2){
    if (coordX1 > coordX2){
        std::swap(coordX1, coordX2);
        std::swap(coordY1, coordY2);
    }
    int deltaX = abs(coordX2 - coordX1);
    int deltaY = abs(coordY2 - coordY1);
    int error = 0;
    int deltaErr = (deltaY + 1);
    int y = coordY1;
    int dirY = coordY2 - coordY1;
    if (dirY > 0){
        dirY = 1;
    } else if (dirY < 0){
        dirY = -1;
    }
    for (size_t i = coordX1; i <= coordX2; ++i){
        canvas[y][i].SetValues(0, 0, 255);
        error += deltaErr;
        if (error >= deltaX + 1){
            y += dirY;
            error -= (deltaX + 1);
        }
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
