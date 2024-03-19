#include "graph.h"


Graph::Graph(size_t verticies_count, size_t edges_count):verticesCount_(verticies_count), edgesCount_(edges_count){
    for (size_t i = 0; i < verticies_count; ++i){
        vertices_.emplace_back(i+1);
    }
}

std::vector<Vertex> Graph::GetVerticies(){
    return vertices_;
}

void Graph::AddEdges(const std::vector<std::pair<size_t, size_t>>& edges){
    for (const std::pair<size_t, size_t>& edge: edges){
        vertices_[edge.first - 1].neighbours_.push_back(&vertices_[edge.second - 1]);
        vertices_[edge.second - 1].neighbours_.push_back(&vertices_[edge.first - 1]);
    }
}

std::vector<size_t> Graph::BFS(size_t vertex_start, std::vector<size_t> verticies_end){
    std::vector<size_t> distances(verticesCount_, 0);
    std::vector<bool> visited(verticesCount_);
    std::queue<size_t> q;
    visited[vertex_start - 1] = 1;
    q.push(vertex_start - 1);
    while ((!q.empty()) && (verticies_end.size()!=0)){
        size_t last = q.front();
        q.pop();
        for (Vertex* vertex: vertices_[last].neighbours_){ 
            if (!visited[vertex->num_ - 1]){
                visited[vertex->num_ - 1] = 1;
                distances[vertex->num_ - 1] = distances[last] + 1;
                q.push(vertex->num_ - 1);
            }
            if (std::find(verticies_end.begin(), verticies_end.end(), vertex->num_)!=verticies_end.end()){
                verticies_end.erase(std::remove(verticies_end.begin(), verticies_end.end(), vertex->num_), verticies_end.end());
            }
        }
    }
    return distances;
}

double Graph::RepulsiveForce(double x){
    return springLength_/(x*x);
}

double Graph::AtractiveForce(double x){
    return (x*x)/springLength_;
}

void Graph::FruchtermanReingoldAlgorithm(size_t width, size_t height, size_t border, size_t max_iterations){
    for (Vertex& vertex: vertices_){
        vertex.position_ = {rand()%int(width), rand()%int(height)};
    }
    size_t area = width * height;
    springLength_ = c_ * sqrt(area / verticesCount_);
    temp_ = sqrt(area);
    size_t iter = 0;
    while (iter < max_iterations){
        for (Vertex& vertex: vertices_){
            //calculate forces for vertex
            for (Vertex& vertex_: vertices_){
                if (vertex.num_ == vertex_.num_) continue;
                Vector dist = vertex.position_ - vertex_.position_;
                vertex.displacement_ = vertex.displacement_ + dist.Normalize()*RepulsiveForce(dist.Distance());
            }
            for (Vertex* next_vertex: vertex.neighbours_){
                Vector dist = vertex.position_ - next_vertex->position_;
                vertex.displacement_ = vertex.displacement_ - dist.Normalize()*AtractiveForce(dist.Distance());
                next_vertex->displacement_ = next_vertex->displacement_ + dist.Normalize()*AtractiveForce(dist.Distance());
            }
        }
        for (Vertex& vertex: vertices_){
            //change coordinates using cool coeff
            vertex.position_ = vertex.position_ + (vertex.displacement_.Normalize()*std::min(vertex.displacement_.Distance(), temp_));
            vertex.position_.SetX(std::min(width - border, std::max(border, static_cast<size_t>(vertex.position_.GetX()))));
            vertex.position_.SetY(std::min(height - border, std::max(border, static_cast<size_t>(vertex.position_.GetY()))));
            vertex.displacement_.SetX(0);
            vertex.displacement_.SetY(0);
        }
        temp_ *= cool_;
        ++iter;
    }
}
