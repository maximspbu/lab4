#include "bmp.h"
#include "reader.h"
#include "drawer.h"

#include <iostream>

int main(){
    Reader reader("../samples/sample2.txt");
    Graph graph(reader.GetVerticiesCount(), reader.GetEdgesCount());
    graph.AddEdges(reader.GetEdges());
    size_t width, height, radius;
    width = 100*floor(sqrt(reader.GetVerticiesCount()));
    height = width;
    radius = 10;
    size_t max_iterations = 100;
    graph.FruchtermanReingoldAlgorithm(width, height, radius + 5, max_iterations);
    std::vector<Vertex> result = graph.GetVerticies();
    Bmp writer(width, height);
    Drawer drawer(width, height, writer.GetDigits());
    for (Vertex& vertex: result){
        for (Vertex* next_vertex: vertex.neighbours_){
            drawer.Line(vertex.position_.GetX(), vertex.position_.GetY(), next_vertex->position_.GetX(), next_vertex->position_.GetY());
        }
    }
    for (Vertex& vertex: result){
        drawer.Circle(vertex.position_.GetX(), vertex.position_.GetY(), radius);
        drawer.Num(vertex.position_.GetX()+radius, vertex.position_.GetY()-radius, vertex.num_);
    }
    writer.Convert(drawer.GetCanvas());
    std::string file_name = "../result/test3.bmp";
    writer.Write(file_name);
    return 0;
}
