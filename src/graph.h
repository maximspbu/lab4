#ifndef GRAPH_H
#define GRAPH_H


#include "vector.h"


#include <cstddef>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <unordered_map>


struct Vertex{
    Vertex(size_t num):num_(num){};
    Vector position;
    Vector disposition;
    size_t num_;
    size_t coord_x_, coord_y_;
    Vector velocity;
    std::vector<Vertex*> next_;
};

class Graph{
    private:
        size_t verticies_count_;
        size_t edges_count_;
        std::vector<bool> visited_;
        std::vector<Vertex> verticies_;
        std::vector<size_t> borders_;
        double l_spring_ = 30.0;
        double damping_ = 0.1;

    public:
        Graph(size_t verticies_count, size_t edges_count);
        std::vector<size_t> BFS(size_t vertex_start, std::vector<size_t> verticies_end);
        void AddVerticies(const std::vector<std::pair<size_t, size_t>>& pairs);
        void DirectedForce(size_t epsilon, size_t max_iterations);
        Vector RepulsiveForce(Vertex v1, Vertex v2);
        Vector AttactiveForce(Vertex v1, Vertex v2);
        std::vector<Vertex> GetVerticies();
};


#endif //GRAPH_H
