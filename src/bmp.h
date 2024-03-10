#ifndef BMP_H
#define BMP_H

#include "pixel.h"

#include <cstddef>
#include <stdint.h>
#include <vector>
#include <fstream>
#include <string>


#pragma pack(push, 1)
struct BMPFileHeader{
    uint16_t file_type{19778};
    uint32_t file_size{54};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{54};
};
#pragma pack(pop)
#pragma pack(push, 1)
struct BMPInfoHeader{
    uint32_t size{40};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bit_count{24};
    uint32_t compression{0};
    uint32_t size_image{0};
    int32_t x_pixels_per_meter{3780};
    int32_t y_pixels_per_meter{3780};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};
#pragma pack(pop)

class Bmp{
    public:
        Bmp(size_t width, size_t height);
        void Write(const std::string &file_name);
        std::vector<uint8_t> Padding(int* row_stride);
        void Convert(const std::vector<std::vector<Pixel>>& canvas);
        std::vector<std::vector<Pixel>> Read(const std::string &file_name);
        std::vector<std::vector<std::vector<Pixel>>> GetDigits();
    private:
        BMPFileHeader file_header_;
        BMPInfoHeader info_header_;
        BMPFileHeader read_file_header_;
        BMPInfoHeader read_info_header_;
        std::vector<uint8_t> canvas_;
        std::vector<std::vector<std::vector<Pixel>>> digits_;
};


#endif //BMP_H
