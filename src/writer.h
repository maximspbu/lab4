#ifndef WRITER_H
#define WRITER_H
#include <cstddef>
#include <stdint.h>
#include <vector>
#include <fstream>
#include <string>

// BMPFileHeader:
// file_type 19778
// file_size 3966390
// reserved1 0
// reserved2 0
// offset_data 54
// BMPInfoHeader:
// info_header 40
// width 1408
// height 939
// planes 1
// bit_count 24
// compression 0
// size_image 0
// x_pixels_per_meter 3780
// y_pixels_per_meter 3780
// colors_used 0
// colors_important 0

//public
//protected
//private

struct BMPFileHeader{
    uint16_t file_type{19778};
    uint32_t file_size{3966390};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{54};
};
#pragma pack(pop)
#pragma pack(push, 1)
struct BMPInfoHeader{
    uint32_t size{40};
    int32_t width{1408};
    int32_t height{939};
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

class Writer{
    public:
        Writer(const std::vector<uint8_t> &canvas);
        void Write(const std::string &file_name);
        std::vector<uint8_t> Padding(int* row_stride);
    private:
        BMPFileHeader file_header_;
        BMPInfoHeader info_header_;
        std::vector<uint8_t> canvas_;
};

#endif //WRITER_H
