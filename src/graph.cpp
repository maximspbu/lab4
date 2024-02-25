#include "graph.h"

Graph::Graph(size_t verticies_count, size_t edges_count):verticies_count_(verticies_count), edges_count_(edges_count){
    for (size_t i = 0; i < verticies_count; ++i){
        verticies_.emplace_back(i+1);
    }
}

void Graph::AddVerticies(std::vector<std::pair<size_t, size_t>> pairs){
    for (size_t i = 0; i < pairs.size(); ++i){
        verticies_[pairs[i].first-1].next_.push_back(&verticies_[pairs[i].second-1]);
        verticies_[pairs[i].second-1].next_.push_back(&verticies_[pairs[i].first-1]);
    }
}

std::vector<size_t> Graph::BFS(size_t vertex_start){
    std::vector<size_t> distances(verticies_count_);
    std::vector<bool> visited(verticies_count_);
    // for (int i = 0; i < visited.size(); ++i){
    //     std::cout << visited[i] << '\n';
    // }
    std::queue<size_t> q;
    distances[vertex_start-1] = 0;
    visited[vertex_start-1] = 1;
    q.push(vertex_start-1);
    while (!q.empty()){
        size_t last = q.front();
        q.pop();
        for (size_t i = 0; i < verticies_[last].next_.size(); ++i){
            if (!visited[(*verticies_[last].next_[i]).num_-1]){
                visited[(*verticies_[last].next_[i]).num_-1] = 1;
                distances[(*verticies_[last].next_[i]).num_-1] = distances[last]+1;
                q.push((*verticies_[last].next_[i]).num_-1);
            }
        }
    }
    // for (size_t i = 0; i < distances.size(); ++i){
    //     std::cout << distances[i] << '\n';
    // }
    return distances;
}

std::vector<std::vector<size_t>> Graph::FiltrationMIS(){
    std::vector<std::vector<size_t>> filtrated_graph;
    std::vector<size_t> all_verticies;
    for (size_t i = 0; i < verticies_count_; ++i){
        all_verticies.push_back(i + 1);
    }
    filtrated_graph.push_back(all_verticies);
    //std::vector<Vertex> iter_verticies(verticies_);
    size_t step = 1;
    while ((filtrated_graph[step - 1].size() > 1)){ //&&(step<=2)
        std::cout << step << ": " << "filt " << filtrated_graph.size() << '\n';
        std::vector<size_t> prev_verticies(filtrated_graph[step - 1]);
        std::vector<size_t> next_verticies;
        while (prev_verticies.size() != 0){
            std::cout << prev_verticies.size() << '\n';
            next_verticies.push_back(prev_verticies[0]);
            std::vector<size_t> distances = BFS(prev_verticies[0]);
            for (size_t i = 0; i < distances.size(); ++i){
                if ((distances[i] > pow(2, step)) && (std::find(prev_verticies.begin(), prev_verticies.end(), i + 1)!=prev_verticies.end())){
                    next_verticies.push_back(i + 1);
                } else {
                    prev_verticies.erase(std::remove(prev_verticies.begin(), prev_verticies.end(), i+1), prev_verticies.end());
                }
            }
            std::cout << step << ": " << "prev " << prev_verticies.size() << '\n';
            std::cout << step << ": " << "next " << next_verticies.size() << '\n';
        }
        step++;
        filtrated_graph.push_back(next_verticies);
    }
    
    for (size_t i = 0; i < filtrated_graph.size(); ++i){
        std::cout << "V_" << i << ":\n";
        for (size_t j = 0; j < filtrated_graph[i].size(); ++j){
            std::cout << filtrated_graph[i][j] << '\n';
        }
    }
    return filtrated_graph;
}
