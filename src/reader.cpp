#include "reader.h"

Reader::Reader(const std::string &filename):filename_(filename){
    file_.open(filename_);
    file_ >> vertices_count_ >> edges_count_;
    size_t vertex1, vertex2;
    for (size_t e = 0; e < edges_count_; ++e){
        file_ >> vertex1 >> vertex2;
        pairs_.emplace_back(vertex1, vertex2);
    }
    file_.close();
}

std::vector<std::pair<size_t, size_t>> Reader::GetPairs(){
    return pairs_;
}

size_t Reader::GetVerticiesCount(){
    return vertices_count_;
}
size_t Reader::GetEdgesCount(){
    return edges_count_;
}
