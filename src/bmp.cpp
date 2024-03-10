#include "bmp.h"
#include <iostream>


Bmp::Bmp(size_t width, size_t height){
    file_header_.file_size+=width*height*3;
    info_header_.width=width;
    info_header_.height=height;
    digits_.resize(10);
    std::string filename;
    for (size_t i = 0; i < 10; ++i){
        filename = "../digits/" + std::to_string(i) + ".bmp";
        digits_[i] = Read(filename);
    }
}

std::vector<uint8_t> Bmp::Padding(int* row_stride){
    *row_stride = info_header_.width*3;
    uint32_t new_stride = *row_stride;
    while (new_stride%4!=0){
        new_stride++;
    }
    std::vector<uint8_t> padding_row(new_stride-*row_stride);
    return padding_row;
}

void Bmp::Convert(const std::vector<std::vector<Pixel>>& canvas){
    for (size_t i = 0; i < canvas.size(); ++i){
        for (size_t j = 0; j < canvas[i].size(); ++j){
            canvas_.push_back(canvas[i][j].blue_);
            canvas_.push_back(canvas[i][j].green_);
            canvas_.push_back(canvas[i][j].red_);
        }
    }
}

void Bmp::Write(const std::string &filename){
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

std::vector<std::vector<Pixel>> Bmp::Read(const std::string &file_name){
    std::vector<std::vector<Pixel>> canvas;
    std::vector<uint8_t> matrix;
    std::ifstream fs{file_name, std::ios_base::binary};
    if (fs.is_open()){
        fs.read((char*)&read_file_header_, sizeof(read_file_header_));
        fs.read((char*)&read_info_header_, sizeof(read_info_header_));
        fs.seekg(read_file_header_.offset_data, fs.beg); // перемещаем указатель на место в файле, где записаны пиксели
        read_file_header_.file_size = read_file_header_.offset_data; // для подсчета размера файла мы пока считаем только размер заголовка
        matrix.resize(read_info_header_.width*read_info_header_.height*3);
        if (read_info_header_.width%4 == 0){
            fs.read((char*)matrix.data(), matrix.size());
            read_file_header_.file_size += static_cast<uint32_t>(matrix.size()); // размер файла уже с учетом вектора пикселей
        } else {
            int row_stride = 0;
            std::vector<uint8_t> padding_row = Padding(&row_stride);
            for (int y = 0; y < read_info_header_.height; ++y){
                fs.read((char*)(matrix.data() + row_stride * y), row_stride);
                fs.read((char*)padding_row.data(), padding_row.size());
            }
            read_file_header_.file_size += static_cast<uint32_t>(matrix.size()) + read_info_header_.height*static_cast<uint32_t>(padding_row.size());
        }
        fs.close();
        for (size_t i = 0; i < read_info_header_.height; ++i){
            canvas.emplace_back();
            for (size_t j = 0; j < read_info_header_.width*3; j+=3){
                canvas[i].emplace_back(matrix[i*read_info_header_.width + j], matrix[i*read_info_header_.width + j + 1], matrix[i*read_info_header_.width + j + 2]);
            }
        }
        return canvas;
    } else {
        std::cout << "No such file found\n";
        exit(0);
    }
}

std::vector<std::vector<std::vector<Pixel>>> Bmp::GetDigits(){
    return digits_;
}
