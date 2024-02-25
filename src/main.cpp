#include "writer.h"
#include "reader.h"
#include <iostream>
//pare file
//c
//c++

int main(){
    Reader reader("../samples/sample1.txt");
    Graph graph(reader.GetVerticiesCount(), reader.GetEdgesCount());
    graph.AddVerticies(reader.GetPairs());
    std::vector<std::vector<size_t>> filtrated_verticies = graph.FiltrationMIS();
    // size_t width, height;
    // width = 1408;
    // height = 939;
    // std::vector<uint8_t> matrix(height*width*3);
    // for (int i = 0; i < matrix.size(); ++i){
    //     matrix[i]=255;
    // }
    // std::cout << size(matrix) << '\n';
    // Writer writer(matrix);
    // std::string file_name = "../result/test.bmp";
    // writer.Write(file_name);
    // return 0;
}
