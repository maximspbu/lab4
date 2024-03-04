#include "writer.h"
#include "reader.h"
#include "drawer.h"
#include <iostream>

int main(){
    Reader reader("../samples/sample1.txt");
    Graph graph(reader.GetVerticiesCount(), reader.GetEdgesCount());
    graph.AddVerticies(reader.GetPairs());
    //std::vector<size_t> filtrated_verticies = graph.FiltrationMIS();
    //graph.BuildSupportVerticies(filtrated_verticies);
    graph.DirectedForce(1, 6);

    size_t width, height;
    width = 1408;
    height = 939;
    std::vector<Vertex> result = graph.GetVerticies();
    Drawer drawer(width, height);
    for (size_t i = 0; i < result.size(); ++i){
        for (size_t j = 0; j < result[i].next_.size(); ++j){
            drawer.line(result[i].position.GetX(), result[i].position.GetY(), result[i].next_[j]->position.GetX(), result[i].next_[j]->position.GetY());
        }
    }
    for (size_t i = 0; i < result.size(); ++i){
        drawer.circle(result[i].position.GetX(), result[i].position.GetY(), 10);
    }
    Writer writer;
    writer.Convert(drawer.GetCanvas());
    std::string file_name = "../result/test3.bmp";
    writer.Write(file_name);
    
    return 0;
}
