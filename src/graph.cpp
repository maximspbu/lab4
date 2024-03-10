#include "graph.h"


Graph::Graph(size_t verticies_count, size_t edges_count):vertices_count_(verticies_count), edges_count_(edges_count){
    for (size_t i = 0; i < verticies_count; ++i){
        vertices_.emplace_back(i+1);
    }
}

std::vector<Vertex> Graph::GetVerticies(){
    return vertices_;
}

void Graph::AddEdges(const std::vector<std::pair<size_t, size_t>>& pairs){
    for (size_t i = 0; i < pairs.size(); ++i){
        vertices_[pairs[i].first - 1].next_.push_back(&vertices_[pairs[i].second - 1]);
        vertices_[pairs[i].second - 1].next_.push_back(&vertices_[pairs[i].first - 1]);
    }
}

std::vector<size_t> Graph::BFS(size_t vertex_start, std::vector<size_t> verticies_end){
    std::vector<size_t> distances(vertices_count_, 0);
    std::vector<bool> visited(vertices_count_);
    std::queue<size_t> q;
    visited[vertex_start - 1] = 1;
    q.push(vertex_start - 1);
    while ((!q.empty()) && (verticies_end.size()!=0)){
        size_t last = q.front();
        q.pop();
        for (size_t i = 0; i < vertices_[last].next_.size(); ++i){
            if (!visited[(*vertices_[last].next_[i]).num_ - 1]){
                visited[(*vertices_[last].next_[i]).num_ - 1] = 1;
                distances[(*vertices_[last].next_[i]).num_ - 1] = distances[last] + 1;
                q.push((*vertices_[last].next_[i]).num_ - 1);
            }
            if (std::find(verticies_end.begin(), verticies_end.end(), vertices_[last].next_[i]->num_)!=verticies_end.end()){
                verticies_end.erase(std::remove(verticies_end.begin(), verticies_end.end(), vertices_[last].next_[i]->num_), verticies_end.end());
            }
        }
    }
    return distances;
}

Vector Graph::RepulsiveForce(Vertex v1, Vertex v2){
    int prox = std::max((v2.disposition-v1.disposition).Distance(), 0.001);
    double force = -c*spring_length_*spring_length_/prox;
    Vector new_vector(force*(v2.disposition-v1.disposition).GetX()/(v1.disposition-v2.disposition).Distance(), force*(v2.disposition-v1.disposition).GetY()/(v1.disposition-v2.disposition).Distance());
    //std::cout << "repulsive force between " << v1.num_ << ' ' << v2.num_ << " is " << force << "= " << new_vector.GetX() << ' ' << new_vector.GetY() << ' ' << (v2.disposition-v1.disposition).Distance() << '\n';
    return new_vector;
}

Vector Graph::AttractiveForce(Vertex v1, Vertex v2){
    int prox = std::max((v2.disposition-v1.disposition).Distance(), 1.);
    double force = prox-spring_length_/v1.next_.size();
    //force = prox*prox/spring_length_;
    Vector new_vector(force*(v2.disposition-v1.disposition).GetX()/(v1.disposition-v2.disposition).Distance(), force*(v2.disposition-v1.disposition).GetY()/(v1.disposition-v2.disposition).Distance());
    //std::cout << "before attactive force between " << v1.num_ << ' ' << v2.num_ << " is " << force << "= " <<  new_vector.GetX() << ' ' << new_vector.GetY() << ' ' << (v2.disposition-v1.disposition).Distance() << '\n';
    new_vector = new_vector - RepulsiveForce(v1, v2);
    //std::cout << "after attactive force between " << v1.num_ << ' ' << v2.num_ << " is " << force << "= " <<  new_vector.GetX() << ' ' << new_vector.GetY() << ' ' << (v2.disposition-v1.disposition).Distance() << '\n';
    return new_vector;
}

double Graph::RF(double x){
    return calc_force*spring_length_/(x*x);
}

double Graph::AF(double x){
    return (x*x)/spring_length_/calc_force;
}

void Graph::FruchtermanReingold(size_t width, size_t height, size_t border, size_t max_iterations){
    for (Vertex& vertex: vertices_){
        Vector new_vector(rand()%width, rand()%height);
        vertex.position = new_vector;
        // std::cout << "vertex" << vertex.num_ << '\n';
        // std::cout << "x: " << vertex.position.GetX() << ' ' << "y: " << vertex.position.GetY() << '\n';
    }
    size_t area = width * height;
    spring_length_ = c * sqrt(area / vertices_count_);
    //std::cout << "spring lenght: " << spring_length_ << '\n';
    temp = sqrt(area); //sqrt(area) / 10
    size_t iter = 0;
    while (iter < max_iterations){
        for (Vertex& vertex: vertices_){
            //calculate force of i vertex
            for (Vertex& vertex_: vertices_){
                if (vertex.num_ == vertex_.num_) continue;
                Vector dist = vertex.position - vertex_.position;
                vertex.disposition = vertex.disposition + dist.Normalize()*RF(dist.Distance());
            }
            for (Vertex* next_vertex: vertex.next_){
                Vector dist = vertex.position - next_vertex->position;
                vertex.disposition = vertex.disposition - dist.Normalize()*AF(dist.Distance());
                //next_vertex->disposition = next_vertex->disposition + dist.Normalize()*AF(dist.Distance());
                //vertex.disposition = vertex.disposition + dist.Normalize()*RF(dist.Distance());
            }
        }
        for (Vertex& vertex: vertices_){
            //change coordinates using cool coeff
            vertex.position = vertex.position + vertex.disposition.Normalize()*std::min(vertex.disposition.Distance(), temp);
            vertex.position.SetX(std::min(width-border, static_cast<size_t>(std::max(double(border), vertex.position.GetX()))));
            vertex.position.SetY(std::min(height-border, static_cast<size_t>(std::max(double(border), vertex.position.GetY()))));
            // std::cout << "vertex" << vertex.num_ << '\n';
            // std::cout << "x: " << vertex.position.GetX() << " y: " << vertex.position.GetY() << '\n';
            vertex.disposition.SetX(0);
            vertex.disposition.SetY(0);
        }
        temp *= cool_;
        ++iter;
    }
}

double Graph::WRF(double x){
    return -force*spring_length_*spring_length_/x;
}

double Graph::WAF(double x, int neightbours_count){
    return x*x/spring_length_;
    // return (x-spring_length_)/neightbours_count;
}

void Graph::Walshaw(size_t width, size_t height, size_t border){
    double distances_sum;
    for (Vertex& vertex: vertices_){
        Vector new_vector(rand()%width, rand()%height);
        vertex.position = new_vector;
        vertex.disposition = new_vector;
        // std::cout << "vertex" << vertex.num_ << '\n';
        // std::cout << "x: " << vertex.position.GetX() << ' ' << "y: " << vertex.position.GetY() << '\n';
    }
    for (Vertex& vertex: vertices_){
        for (Vertex* next_vertex: vertex.next_){
            distances_sum += (vertex.position-next_vertex->position).Distance();
        }
    }
    spring_length_ = distances_sum/edges_count_; //if edges_count_==0
    std::cout << spring_length_ << '\n';
    temp = spring_length_/5;
    bool converged = false;
    while (!converged){
        converged = true;
        for (Vertex& vertex: vertices_){
            //change coordinates using cool coeff
            vertex.position = vertex.disposition;
            vertex.position.SetX(std::min(width-border, static_cast<size_t>(std::max(double(border), vertex.position.GetX()))));
            vertex.position.SetY(std::min(height-border, static_cast<size_t>(std::max(double(border), vertex.position.GetY()))));
            // std::cout << "vertex" << vertex.num_ << '\n';
            // std::cout << "x: " << vertex.position.GetX() << " y: " << vertex.position.GetY() << '\n';
        }
        for (Vertex& vertex: vertices_){
            Vector force_vector;
            for (Vertex& vertex_: vertices_){
                if (vertex.num_ == vertex_.num_) continue;
                Vector dist = vertex_.position - vertex.position;
                force_vector = force_vector + dist.Normalize()*WRF(dist.Distance());
            }
            for (Vertex* next_vertex_: vertex.next_){
                Vector dist = next_vertex_->position - vertex.position;
                force_vector = force_vector + dist.Normalize()*WAF(dist.Distance(), vertex.next_.size());
            }
            vertex.disposition = vertex.disposition + force_vector.Normalize()*std::min(temp, force_vector.Distance());
            //std::cout << "dispos: " << vertex.num_ << " x: " << vertex.disposition.GetX() << " y: " << vertex.disposition.GetY() << '\n';
            vertex.disposition.SetX(std::min(width-border, static_cast<size_t>(std::max(double(border), vertex.disposition.GetX()))));
            vertex.disposition.SetY(std::min(height-border, static_cast<size_t>(std::max(double(border), vertex.disposition.GetY()))));
            Vector dist = vertex.disposition - vertex.position;
            //std::cout << "dist: " << dist.Distance() << " calcs: " << spring_length_*tolerance << '\n';
            if (dist.Distance() > spring_length_*tolerance) converged = false;
        }
        temp *= cool_;
    }
    // for (Vertex& vertex: vertices_){
    //     std::cout << "vertex" << vertex.num_ << '\n';
    //     std::cout << "x: " << vertex.position.GetX() << " y: " << vertex.position.GetY() << '\n';
    // }
}
