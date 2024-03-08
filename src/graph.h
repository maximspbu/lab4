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
        void FruchtermanReingold(size_t width, size_t height, size_t border, size_t max_iterations);
        void Walshaw(size_t width, size_t height, size_t border);
        double WRF(double x);
        double WAF(double x, int neighbours_count);
        Vector RepulsiveForce(Vertex v1, Vertex v2);
        Vector AttractiveForce(Vertex v1, Vertex v2);
        double RF(double x);
        double AF(double x);
        std::vector<Vertex> GetVerticies();
    private:
        size_t vertices_count_;
        size_t edges_count_;
        std::vector<Vertex> vertices_;
        std::vector<size_t> borders_;
        double spring_length_; //CAPSLOCK
        const double cool_ = 0.95; //CAPSLOCK
        double temp;
        const double c = 6.0; //CAPSLOCK
        const double calc_force = 1.0; //CAPSLOCK

        const double force = 0.1; //CAPSLOCK
        const double tolerance = 0.01; //CAPSLOCK
};

#endif //GRAPH_H
