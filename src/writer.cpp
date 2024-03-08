#include "writer.h"
#include <iostream>


Writer::Writer(size_t width, size_t height){
    file_header_.file_size+=width*height*3;
    info_header_.width=width;
    info_header_.height=height;
}

std::vector<uint8_t> Writer::Padding(int* row_stride){
    *row_stride = info_header_.width*3;
    uint32_t new_stride = *row_stride;
    while (new_stride%4!=0){
        new_stride++;
    }
    std::vector<uint8_t> padding_row(new_stride-*row_stride);
    return padding_row;
}

void Writer::Convert(const std::vector<std::vector<Pixel>>& canvas){
    for (size_t i = 0; i < canvas.size(); ++i){
        for (size_t j = 0; j < canvas[i].size(); ++j){
            canvas_.push_back(canvas[i][j].blue_);
            canvas_.push_back(canvas[i][j].green_);
            canvas_.push_back(canvas[i][j].red_);
        }
    }
}

void Writer::Write(const std::string &filename){
    std::ofstream of{filename, std::ios_base::binary};
    if (info_header_.width%4==0){
        of.write((const char*)&file_header_, sizeof(file_header_)); //static_cast
        of.write((const char*)&info_header_, sizeof(info_header_));
        of.write((const char*)canvas_.data(), canvas_.size());
    } else {
            int row_stride = 0;
            std::vector<uint8_t> padding_row = Padding(&row_stride);
            of.write((const char*)&file_header_, sizeof(file_header_));
            of.write((const char*)&info_header_, sizeof(info_header_));
            for (size_t y = 0; y < info_header_.height; ++y){
                of.write((const char*)(canvas_.data() + row_stride * y), row_stride);
                of.write((const char*)padding_row.data(), padding_row.size());
            }
    }
    of.close();
}
