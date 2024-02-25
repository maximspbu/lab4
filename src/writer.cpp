#include "writer.h"
#include <iostream>

Writer::Writer(const std::vector<uint8_t> &canvas): canvas_(canvas){

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

void Writer::Write(const std::string &filename){
    std::ofstream of{filename, std::ios_base::binary};
    std::cout<<"BMPFileHeader:\n";
    std::cout<<"file_type"<<' '<<file_header_.file_type <<'\n';
    std::cout<<"file_size"<<' '<<file_header_.file_size <<'\n';
    std::cout<<"reserved1"<<' '<<file_header_.reserved1 <<'\n';
    std::cout<<"reserved2"<<' '<<file_header_.reserved2 <<'\n';
    std::cout<<"offset_data"<<' '<<file_header_.offset_data <<'\n';
    std::cout<<"BMPInfoHeader:\n";
    std::cout<<"info_header"<<' '<<info_header_.size <<'\n';
    std::cout<<"width"<<' '<<info_header_.width <<'\n';
    std::cout<<"height"<<' '<<info_header_.height <<'\n';
    std::cout<<"planes"<<' '<<info_header_.planes <<'\n';
    std::cout<<"bit_count"<<' '<<info_header_.bit_count <<'\n';
    std::cout<<"compression"<<' '<<info_header_.compression <<'\n';
    std::cout<<"size_image"<<' '<<info_header_.size_image <<'\n';
    std::cout<<"x_pixels_per_meter"<<' '<<info_header_.x_pixels_per_meter <<'\n';
    std::cout<<"y_pixels_per_meter"<<' '<<info_header_.y_pixels_per_meter <<'\n';
    std::cout<<"colors_used"<<' '<<info_header_.colors_used <<'\n';
    std::cout<<"colors_important"<<' '<<info_header_.colors_important <<'\n';
    if (info_header_.width%4==0){
        of.write((const char*)&file_header_, sizeof(file_header_));
        of.write((const char*)&info_header_, sizeof(info_header_));
        of.write((const char*)canvas_.data(), canvas_.size());
    } else {
            int row_stride = 0;
            std::vector<uint8_t> padding_row = Padding(&row_stride);
            of.write((const char*)&file_header_, sizeof(file_header_));
            of.write((const char*)&info_header_, sizeof(info_header_));
            for (int y = 0; y < info_header_.height; ++y){ //prefix
                of.write((const char*)(canvas_.data() + row_stride * y), row_stride);
                of.write((const char*)padding_row.data(), padding_row.size());
            }
    }
    of.close();
}
