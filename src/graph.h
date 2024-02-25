#ifndef GRAPH_H
#define GRAPH_H

#include <cstddef>
#include <vector>
#include <queue>
#include <iostream>
#include <cmath>
#include <algorithm>

struct Vertex{
    Vertex(size_t num):num_(num){};
    size_t num_;
    size_t coord_x_, coord_y_;
    std::vector<Vertex*> next_;
};

class Graph{
    private:
        size_t verticies_count_;
        size_t edges_count_;
        std::vector<bool> visited_;
        std::vector<Vertex> verticies_;
    public:
        Graph(size_t verticies_count, size_t edges_count);
        std::vector<size_t> BFS(size_t vertex_start);
        void AddVerticies(std::vector<std::pair<size_t, size_t>> pairs);
        std::vector<std::vector<size_t>> FiltrationMIS();
};

#endif //GRAPH_H
