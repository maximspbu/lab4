#include "writer.h"
#include "reader.h"
#include "drawer.h"
#include <iostream>

int main(){
    Reader reader("../samples/sample1.txt");
    Graph graph(reader.GetVerticiesCount(), reader.GetEdgesCount());
    graph.AddEdges(reader.GetPairs());
    size_t width, height;
    width = 100;
    height = 100;
    graph.FruchtermanReingold(width*height);
    //std::vector<Vertex> result = graph.GetVerticies();
    // Drawer drawer(width, height);
    // for (size_t i = 0; i < result.size(); ++i){
    //     for (size_t j = 0; j < result[i].next_.size(); ++j){
    //         drawer.line(result[i].position.GetX(), result[i].position.GetY(), result[i].next_[j]->position.GetX(), result[i].next_[j]->position.GetY());
    //     }
    // }
    // for (size_t i = 0; i < result.size(); ++i){
    //     drawer.circle(result[i].position.GetX(), result[i].position.GetY(), 10);
    // }
    // Writer writer;
    // writer.Convert(drawer.GetCanvas());
    // std::string file_name = "../result/test3.bmp";
    // writer.Write(file_name);
    return 0;
}
