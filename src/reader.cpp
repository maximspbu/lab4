#include "reader.h"


Reader::Reader(const std::string &filename):filename_(filename){
    file_.open(filename_);
    file_ >> verticesCount_ >> edgesCount_;
    size_t vertex1, vertex2;
    for (size_t e = 0; e < edgesCount_; ++e){
        file_ >> vertex1 >> vertex2;
        edges_.emplace_back(vertex1, vertex2);
    }
    file_.close();
}

std::vector<std::pair<size_t, size_t>> Reader::GetEdges(){
    return edges_;
}

size_t Reader::GetVerticiesCount(){
    return verticesCount_;
}

size_t Reader::GetEdgesCount(){
    return edgesCount_;
}
