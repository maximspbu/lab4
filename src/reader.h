#ifndef READER_H
#define READER_H

#include "graph.h"
#include <vector>
#include <string>
#include <fstream>

class Reader{
    public:
        Reader(const std::string &filename);
        std::vector<std::pair<size_t, size_t>> GetPairs();
        size_t GetVerticiesCount();
        size_t GetEdgesCount();
    private:
        std::string filename_;
        std::ifstream file_;
        size_t vertices_count_, edges_count_;
        std::vector<std::pair<size_t, size_t>> pairs_;
};

#endif //READER_H
