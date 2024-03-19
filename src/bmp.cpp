#include "bmp.h"
#include <iostream>


Bmp::Bmp(size_t width, size_t height){
    fileHeader_.file_size += width*height*3;
    infoHeader_.width = width;
    infoHeader_.height = height;
    digits_.resize(10);
    std::string filename;
    for (size_t i = 0; i < 10; ++i){
        filename = "../digits/" + std::to_string(i) + ".bmp";
        digits_[i] = Read(filename);
    }
}

std::vector<uint8_t> Bmp::Padding(int* row_stride){
    *row_stride = infoHeader_.width*3;
    uint32_t new_stride = *row_stride;
    while (new_stride%4 != 0){
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
    if (infoHeader_.width%4 == 0){
        of.write((const char*)&fileHeader_, sizeof(fileHeader_)); //static_cast
        of.write((const char*)&infoHeader_, sizeof(infoHeader_));
        of.write((const char*)canvas_.data(), canvas_.size());
    } else {
            int row_stride = 0;
            std::vector<uint8_t> padding_row = Padding(&row_stride);
            of.write((const char*)&fileHeader_, sizeof(fileHeader_));
            of.write((const char*)&infoHeader_, sizeof(infoHeader_));
            for (size_t y = 0; y < infoHeader_.height; ++y){
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
        fs.read((char*)&readFileHeader_, sizeof(readFileHeader_));
        fs.read((char*)&readInfoHeader_, sizeof(readInfoHeader_));
        fs.seekg(readFileHeader_.offset_data, fs.beg);
        readFileHeader_.file_size = readFileHeader_.offset_data;
        matrix.resize(readInfoHeader_.width*readInfoHeader_.height * 3);
        if (readInfoHeader_.width % 4 == 0){
            fs.read((char*)matrix.data(), matrix.size());
            readFileHeader_.file_size += static_cast<uint32_t>(matrix.size());
        } else {
            int row_stride = 0;
            std::vector<uint8_t> padding_row = Padding(&row_stride);
            for (int y = 0; y < readInfoHeader_.height; ++y){
                fs.read((char*)(matrix.data() + row_stride * y), row_stride);
                fs.read((char*)padding_row.data(), padding_row.size());
            }
            readFileHeader_.file_size += static_cast<uint32_t>(matrix.size()) + readInfoHeader_.height*static_cast<uint32_t>(padding_row.size());
        }
        fs.close();
        canvas.resize(readInfoHeader_.height);
        for (size_t i = 0; i < readInfoHeader_.height; ++i){
            for (size_t j = 0; j < readInfoHeader_.width*3; j += 3){
                //std::cout << matrix[i*readInfoHeader_.width + j] << ' ' << matrix[i*readInfoHeader_.width + j + 1] << ' ' << matrix[i*readInfoHeader_.width + j + 2] << '\n';
                canvas[i].emplace_back(matrix[i*readInfoHeader_.width*3 + j], matrix[i*readInfoHeader_.width*3 + j + 1], matrix[i*readInfoHeader_.width*3 + j + 2]);
                //canvas[i].emplace_back(static_cast<uint8_t>(matrix[i*readInfoHeader_.width + j]), static_cast<uint8_t>(matrix[i*readInfoHeader_.width + j + 1]), static_cast<uint8_t>(matrix[i*readInfoHeader_.width + j + 2]));
                //std::cout << canvas[i][j/3].blue_ << ' ' << canvas[i][j/3].green_ << ' ' << canvas[i][j/3].red_ << '\n';
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
