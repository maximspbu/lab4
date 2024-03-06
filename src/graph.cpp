#include "graph.h"


Graph::Graph(size_t verticies_count, size_t edges_count):vertices_count_(verticies_count), edges_count_(edges_count){
    for (size_t i = 0; i < verticies_count; ++i){
        verticies_.emplace_back(i+1);
    }
}

std::vector<Vertex> Graph::GetVerticies(){
    return verticies_;
}

void Graph::AddEdges(const std::vector<std::pair<size_t, size_t>>& pairs){
    for (size_t i = 0; i < pairs.size(); ++i){
        verticies_[pairs[i].first - 1].next_.push_back(&verticies_[pairs[i].second - 1]);
        verticies_[pairs[i].second - 1].next_.push_back(&verticies_[pairs[i].first - 1]);
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
        for (size_t i = 0; i < verticies_[last].next_.size(); ++i){
            if (!visited[(*verticies_[last].next_[i]).num_ - 1]){
                visited[(*verticies_[last].next_[i]).num_ - 1] = 1;
                distances[(*verticies_[last].next_[i]).num_ - 1] = distances[last] + 1;
                q.push((*verticies_[last].next_[i]).num_ - 1);
            }
            if (std::find(verticies_end.begin(), verticies_end.end(), verticies_[last].next_[i]->num_)!=verticies_end.end()){
                verticies_end.erase(std::remove(verticies_end.begin(), verticies_end.end(), verticies_[last].next_[i]->num_), verticies_end.end());
            }
        }
    }
    return distances;
}

Vector Graph::RepulsiveForce(Vertex v1, Vertex v2){
    int prox = std::max((v2.disposition-v1.disposition).Distance(), 0.001);
    double force = -c*l_spring_*l_spring_/prox;
    Vector new_vector(force*(v2.disposition-v1.disposition).GetX()/(v1.disposition-v2.disposition).Distance(), force*(v2.disposition-v1.disposition).GetY()/(v1.disposition-v2.disposition).Distance());
    std::cout << "repulsive force between " << v1.num_ << ' ' << v2.num_ << " is " << force << "= " << new_vector.GetX() << ' ' << new_vector.GetY() << ' ' << (v2.disposition-v1.disposition).Distance() << '\n';
    return new_vector;
}

Vector Graph::AttractiveForce(Vertex v1, Vertex v2){
    int prox = std::max((v2.disposition-v1.disposition).Distance(), 1.);
    double force = prox-l_spring_/v1.next_.size();
    //force = prox*prox/l_spring_;
    Vector new_vector(force*(v2.disposition-v1.disposition).GetX()/(v1.disposition-v2.disposition).Distance(), force*(v2.disposition-v1.disposition).GetY()/(v1.disposition-v2.disposition).Distance());
    std::cout << "before attactive force between " << v1.num_ << ' ' << v2.num_ << " is " << force << "= " <<  new_vector.GetX() << ' ' << new_vector.GetY() << ' ' << (v2.disposition-v1.disposition).Distance() << '\n';
    new_vector = new_vector - RepulsiveForce(v1, v2);
    std::cout << "after attactive force between " << v1.num_ << ' ' << v2.num_ << " is " << force << "= " <<  new_vector.GetX() << ' ' << new_vector.GetY() << ' ' << (v2.disposition-v1.disposition).Distance() << '\n';
    return new_vector;
}

void Graph::FruchtermanReingold(size_t area){
    std::vector<Vertex> new_verticies = verticies_;
    for (size_t i = 0; i < vertices_count_; ++i){
        Vector new_vector(rand()%25, rand()%25);
        new_verticies[i].position = new_vector;
        new_verticies[i].disposition = new_vector;
    }
    double sum = 0;
    for (size_t i = 0; i < new_verticies.size(); ++i){
        std::cout << "vertex" << new_verticies[i].num_ << '\n';
        std::cout << "x: " << new_verticies[i].position.GetX() << ' ' << "y: " << new_verticies[i].position.GetY() << '\n';
        for (size_t j = 0; j < new_verticies.size(); ++j){
            sum += (new_verticies[i].disposition-new_verticies[j].disposition).Distance();
        }
    }
    l_spring_ = sum / edges_count_;
    std::cout << "spring lenght: " << l_spring_ << '\n';
    temp = l_spring_ / 2;
    bool complete = false;
    while (complete == false){
        complete = true;
        for (size_t i = 0; i < vertices_count_; ++i){
            //change coordinates using cool coeff
            new_verticies[i].position = new_verticies[i].disposition;
            std::cout << "vertex" << new_verticies[i].num_ << '\n';
            std::cout << "x: " << new_verticies[i].position.GetX() << " y: " << new_verticies[i].position.GetY() << '\n';
        }
        for (size_t i = 0; i < vertices_count_; ++i){
            //calculate force of i vertex
            Vector calc_force(0,0);
            for (size_t j = 0; j < vertices_count_; ++j){
                if (i == j) continue;
                Vector dist = new_verticies[i].disposition - new_verticies[j].disposition;
                calc_force = calc_force + RepulsiveForce(new_verticies[i], new_verticies[j]);
            }
            for (size_t j = 0; j < new_verticies[i].next_.size(); ++j){
                Vector dist = new_verticies[i].disposition - new_verticies[i].next_[j]->disposition;
                calc_force = calc_force + AttractiveForce(new_verticies[i], new_verticies[new_verticies[i].next_[j]->num_-1]);
            }
            std::cout << "force:" << calc_force.GetX() << ' ' << calc_force.GetY() << '\n';
            std::cout << "min: " << std::min(temp, calc_force.Distance()) << '\n';
            new_verticies[i].velocity = new_verticies[i].velocity + (calc_force) * std::min(temp, calc_force.Distance());
            new_verticies[i].disposition = new_verticies[i].disposition + new_verticies[i].velocity;
            std::cout << "velocity: " << new_verticies[i].velocity.GetX() << ' ' << new_verticies[i].velocity.GetY() << '\n';
            if ((new_verticies[i].position-new_verticies[i].disposition).Distance()>l_spring_*tol){
                complete = false;
            }
            for (size_t i = 0; i < vertices_count_; ++i){
                std::cout << "vertex" << new_verticies[i].num_ << '\n';
                std::cout << "x: " << new_verticies[i].disposition.GetX() << ' ' << "y: " << new_verticies[i].disposition.GetY() << '\n';
            }
        }
        temp *= cool_;
        break;
    }
    double minX = new_verticies[0].disposition.GetX();
    double minY = new_verticies[0].disposition.GetY();
    for (size_t i = 0; i < new_verticies.size(); ++i){
        minX = std::min(minX, new_verticies[i].position.GetX());
        minY = std::min(minY, new_verticies[i].position.GetY());
    }
    for (size_t i = 0; i < new_verticies.size(); ++i){
        std::cout << "vertex" << new_verticies[i].num_ << '\n';
        std::cout << "x: " << new_verticies[i].disposition.GetX() << ' ' << "y: " << new_verticies[i].disposition.GetY() << '\n';
    }
    // if ((minX<11)||(minY<11)){
    //     Vector vector_shift(-minX+11, -minY+11);
    //     for (size_t i = 0; i < new_verticies.size(); ++i){
    //         std::cout << "vertex" << new_verticies[i].num_ << '\n';
    //         new_verticies[i].position = new_verticies[i].position + vector_shift;
    //         std::cout << "x: " << new_verticies[i].position.GetX() << ' ' << "y: " << new_verticies[i].position.GetY() << '\n';
    //         verticies_[i] = new_verticies[i];
    //     }
    // }
    l_spring_ *= sqrt(7/4);
}
