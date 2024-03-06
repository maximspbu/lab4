#ifndef GRAPH_H
#define GRAPH_H


#include "vector.h"


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
    public:
        Graph(size_t vertices_count, size_t edges_count);
        std::vector<size_t> BFS(size_t vertex_start, std::vector<size_t> verticies_end);
        void AddEdges(const std::vector<std::pair<size_t, size_t>>& pairs);
        void FruchtermanReingold(size_t area);
        Vector RepulsiveForce(Vertex v1, Vertex v2);
        Vector AttractiveForce(Vertex v1, Vertex v2);
        std::vector<Vertex> GetVerticies();
    private:
        size_t vertices_count_;
        size_t edges_count_;
        std::vector<Vertex> verticies_;
        std::vector<size_t> borders_;
        double l_spring_;
        const double cool_ = 0.9;
        double temp;
        const double c = 0.01;
        const double tol = 0.001;
};

#endif //GRAPH_H
