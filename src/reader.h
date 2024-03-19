#ifndef READER_H
#define READER_H


#include "graph.h"
#include <vector>
#include <string>
#include <fstream>


class Reader{
    public:
        Reader(const std::string &filename);
        std::vector<std::pair<size_t, size_t>> GetEdges();
        size_t GetVerticiesCount();
        size_t GetEdgesCount();

    private:
        std::string filename_;
        std::ifstream file_;
        size_t verticesCount_, edgesCount_;
        std::vector<std::pair<size_t, size_t>> edges_;
};

#endif //READER_H
