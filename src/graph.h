#ifndef GRAPH_H
#define GRAPH_H


#include "point.h"


#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <unordered_map>


struct Vertex{
    Vertex(size_t num):num_(num){};
    Point position_;
    Vector displacement_;
    size_t num_;
    std::vector<Vertex*> neighbours_;
};

class Graph{
    public:
        Graph(size_t vertices_count, size_t edges_count);
        std::vector<size_t> BFS(size_t vertex_start, std::vector<size_t> vertices_end);
        void AddEdges(const std::vector<std::pair<size_t, size_t>>& edges);
        void FruchtermanReingoldAlgorithm(size_t width, size_t height, size_t border, size_t maxIterations);
        double RepulsiveForce(double x);
        double AtractiveForce(double x);
        std::vector<Vertex> GetVerticies();
    private:
        size_t verticesCount_;
        size_t edgesCount_;
        std::vector<Vertex> vertices_;
        double springLength_;
        const double cool_ = 0.95;
        double temp_;
        const double c_ = 20.0;
};

#endif //GRAPH_H
