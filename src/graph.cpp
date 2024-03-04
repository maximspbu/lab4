#include "graph.h"


Graph::Graph(size_t verticies_count, size_t edges_count):verticies_count_(verticies_count), edges_count_(edges_count){
    for (size_t i = 0; i < verticies_count; ++i){
        verticies_.emplace_back(i+1);
    }
}

std::vector<Vertex> Graph::GetVerticies(){
    return verticies_;
}

void Graph::AddVerticies(const std::vector<std::pair<size_t, size_t>>& pairs){
    for (size_t i = 0; i < pairs.size(); ++i){
        verticies_[pairs[i].first - 1].next_.push_back(&verticies_[pairs[i].second - 1]);
        verticies_[pairs[i].second - 1].next_.push_back(&verticies_[pairs[i].first - 1]);
    }
}

std::vector<size_t> Graph::BFS(size_t vertex_start, std::vector<size_t> verticies_end){
    std::vector<size_t> distances(verticies_count_, 0);
    std::vector<bool> visited(verticies_count_);
    // for (int i = 0; i < visited.size(); ++i){
    //     std::cout << visited[i] << '\n';
    // }
    std::queue<size_t> q;
    visited[vertex_start - 1] = 1;
    q.push(vertex_start - 1);
    while ((!q.empty())&&(verticies_end.size()!=0)){
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
    // for (size_t i = 0; i < distances.size(); ++i){
    //     std::cout << distances[i] << '\n';
    // }
    return distances;
}
// std::vector<std::vector<size_t>> filtrated_graph;
//     std::vector<size_t> v0;
//     for (size_t i = 0; i < verticies_count_; ++i){
//         v0.push_back(i + 1);
//     }
//     filtrated_graph.push_back(v0);
//     //std::vector<Vertex> iter_verticies(verticies_);
//     size_t step = 1;
//     size_t rand_num;
//     while ((filtrated_graph[step - 1].size() > 2)){ //&&(step<=2)
//         std::cout << step << ": " << "filt " << filtrated_graph.size() << '\n';
//         std::vector<size_t> v_old(filtrated_graph[step - 1]);
//         std::vector<size_t> v_new;
//         std::vector<bool> v_added(verticies_count_, 0);
//         while (v_old.size() != 0){
//             std::cout << "prev_verticies: \n";
//             for (size_t i = 0; i < v_old.size(); ++i){
//                 std::cout << v_old[i] << '\n';
//             }
//             std::cout << "prev_verticies size:\n";
//             std::cout << v_old.size() << '\n';
//             rand_num = std::rand()%v_old.size();
//             while (v_added[rand_num]==1){
//                 rand_num = std::rand()%v_old.size();
//             }
//             std::cout << "choosen rand vert: " << v_old[rand_num] << '\n';
//             v_new.push_back(v_old[rand_num]);
//             std::vector<size_t> distances = BFS(v_old[rand_num], v_old);
//             v_added[rand_num] = 1;
//             for (size_t i = 0; i < distances.size(); ++i){
//                 if ((distances[i] <= (pow(2, step-1) + 1))){
//                     v_old.erase(std::remove(v_old.begin(), v_old.end(), i + 1), v_old.end());
//                     v_added[i] = 1;
//                 }
//                 if ((distances[i] > (pow(2, step-1) + 1)) && (v_added[i]==0)){
//                     v_new.push_back(i + 1);
//                     v_added[i] = 1;
//                 }
//             }
//             std::cout << "after:\n";
//             std::cout << "prev_verticies: \n";
//             for (size_t i = 0; i < v_old.size(); ++i){
//                 std::cout << v_old[i] << '\n';
//             }
//             std::cout << "prev_verticies size:\n";
//             std::cout << v_old.size() << '\n';
//         }
//         step++;
//         filtrated_graph.push_back(v_new);
//     }
    
//     for (size_t i = 0; i < filtrated_graph.size(); ++i){
//         std::cout << "V_" << i << ":\n";
//         for (size_t j = 0; j < filtrated_graph[i].size(); ++j){
//             std::cout << filtrated_graph[i][j] << '\n';
//         }
//     }
//     return filtrated_graph;

// std::vector<size_t> Graph::FiltrationMIS(){
//     std::vector<std::vector<size_t>> result;
//     std::vector<size_t> v0;
//     for (size_t i = 0; i < verticies_count_; ++i){
//         v0.push_back(i + 1);
//     }
//     size_t iter = 1;
//     //std::vector<size_t> already used as rand verticies;
//     bool flag = true;
//     while (flag){
//         result.clear();
//         result.push_back(v0);
//         size_t iter = 1;
//         while (result.back().size() > 3){
//             std::vector<size_t> v_curr = result.back();
//             std::vector<size_t> v_new;
//             std::vector<bool> visited(verticies_count_, 0);
//             while (v_curr.size() != 0){
//                 size_t rand_num = std::rand() % v_curr.size();
//                 v_new.push_back(v_curr[rand_num]);
//                 std::cout << "new rand v: " << v_curr[rand_num] << '\n';
//                 v_curr.erase(std::remove(v_curr.begin(), v_curr.end(), v_curr[rand_num]), v_curr.end());
//                 std::vector<size_t> distances = BFS(v_curr[rand_num], v_curr);
//                 for (size_t i = 0; i < distances.size(); ++i){
//                     if (distances[i] <= (pow(2, iter - 1) + 1)){
//                         v_curr.erase(std::remove(v_curr.begin(), v_curr.end(), i + 1), v_curr.end());
//                     }
//                 }
//             }
//             ++iter;
//             result.push_back(v_new);
//         }
//         if (result.back().size()==3){
//             flag=false;
//         }
//     }
//     std::vector<size_t> v_repeated;
//     std::vector<size_t> rresult;
//     size_t last_border_size = 0;
//     for (int i = result.size() - 1; i > -1; i--){
//         std::cout << "V_" << i << ":\n";
//         borders_.push_back(result[i].size() + last_border_size);
//         last_border_size += result[i].size();
//         for (size_t j = 0; j < result[i].size(); j++){
//             if (std::find(v_repeated.begin(), v_repeated.end(), result[i][j]) == v_repeated.end()){
//                 rresult.push_back(result[i][j]);
//                 v_repeated.push_back(result[i][j]);
//             }
//             std::cout << result[i][j] << '\n';
//         }
//     }
//     // std::cout << "result:\n";
//     // for (size_t i = 0; i < rresult.size(); ++i){
//     //     std::cout << rresult[i] << '\n';
//     // }
//     return rresult;
// }

// void Graph::BuildSupportVerticies(const std::vector<size_t>& filtrated_graph){
//     std::vector<size_t> triangle(3, 0);
//     std::vector<size_t> v_builden = {filtrated_graph[0], filtrated_graph[1], filtrated_graph[2]};
//     std::vector<size_t> distances = BFS(filtrated_graph[0], triangle);
//     triangle[0] = distances[filtrated_graph[1]];
//     triangle[2] = distances[filtrated_graph[2]];
//     distances = BFS(filtrated_graph[1], triangle);
//     triangle[1] = distances[filtrated_graph[2]];

//     verticies_[filtrated_graph[0]].coord_x_ = 0;
//     verticies_[filtrated_graph[0]].coord_y_ = 0;

//     verticies_[filtrated_graph[1]].coord_x_ = 50;
//     verticies_[filtrated_graph[1]].coord_y_ = 0;

//     verticies_[filtrated_graph[2]].coord_x_ = 25;
//     verticies_[filtrated_graph[2]].coord_y_ = 43;

//     for (size_t i = 0; i < borders_.size(); ++i){
//         //move to here
//     }    

//     for (size_t i = 3; i < filtrated_graph.size(); ++i){
//         distances = BFS(filtrated_graph[i], v_builden);
//         size_t vert1_num, vert2_num, vert3_num, dist1, dist2, dist3;
//         dist1 = dist2 = dist3 = pow(2, 32);
//         for (size_t j = 0; j < distances.size(); ++j){
//             if ((std::find(v_builden.begin(), v_builden.end(), j + 1) == v_builden.end())||(distances[j] == 0)){
//                 continue;
//             }
//             if (distances[j] < dist1){
//                 if (dist1 < dist2){
//                     if (dist3 > dist2){
//                         dist3 = dist2;
//                         vert3_num = vert2_num;
//                     }
//                     dist2 = dist1;
//                     vert2_num = vert1_num;
//                 } else if (dist1 < dist3){
//                     dist3 = dist1;
//                     vert3_num = vert1_num;
//                 }
//                 dist1 = distances[j];
//                 vert1_num = j + 1;
//             } else if (distances[j] < dist2) {
//                 if (dist3 > dist2){
//                     dist3 = dist2;
//                     vert3_num = vert2_num;
//                 }
//                 dist2 = distances[j];
//                 vert2_num = j + 1;
//             } else if (distances[j] < dist3) {
//                 dist3 = distances[j];
//                 vert3_num = j + 1;
//             }
//             // if ((i==16)){
//             //     std::cout << "vert1: " << vert1_num << '\n';
//             //     std::cout << "dist1: " << dist1 << '\n';
//             //     std::cout << "vert2: " << vert2_num << '\n';
//             //     std::cout << "dist2: " << dist2 << '\n';
//             //     std::cout << "vert3: " << vert3_num << '\n';
//             //     std::cout << "dist3: " << dist3 << '\n';
//             // }
//         }
//         v_builden.push_back(filtrated_graph[i]);
//         // std::cout << "curr vert: " << filtrated_graph[i] << '\n';
//         // std::cout << "vert1: " << vert1_num << '\n';
//         // std::cout << "dist1: " << dist1 << '\n';
//         // std::cout << "vert2: " << vert2_num << '\n';
//         // std::cout << "dist2: " << dist2 << '\n';
//         // std::cout << "vert3: " << vert3_num << '\n';
//         // std::cout << "dist3: " << dist3 << '\n';
//         // std::cout << "v_builden:\n";
//         // for (size_t x = 0; x < distances.size(); ++x){
//         //     std::cout << x+1 <<": " << distances[x] << '\n';
//         // }
//     }

// }

Vector Graph::RepulsiveForce(Vertex v1, Vertex v2){
    //(-10000)/(pow(max((v1.disposition-v2.disposition).Distance(), 1),2))
    //Vector new_vector((v1.disposition-v2.disposition)*l_spring_*l_spring_/std::max(((v1.disposition-v2.disposition).Distance()), 1.));
    int prox = std::max((v1.disposition-v2.disposition).Distance(), 0.1);
    double force = -(10000/pow(prox, 2));
    //force = l_spring_*l_spring_/prox;
    //new_vector.SetX(new_vector.Distance()*(new_vector.GetX()));
    Vector new_vector(force*(v1.disposition-v2.disposition).GetX()/(v1.disposition-v2.disposition).Distance(), force*(v1.disposition-v2.disposition).GetY()/(v1.disposition-v2.disposition).Distance());
    return new_vector;
    //return (v1.disposition-v2.disposition)*l_spring_*l_spring_/std::max(((v1.disposition-v2.disposition).Distance()), 1.);
}

Vector Graph::AttactiveForce(Vertex v1, Vertex v2){
    int prox = std::max((v1.disposition-v2.disposition).Distance(), 1.);
    double force = 0.1*std::max(prox-l_spring_, 0.);
    //force = prox*prox/l_spring_;
    Vector new_vector(force*(v1.disposition-v2.disposition).GetX()/(v1.disposition-v2.disposition).Distance(), force*(v1.disposition-v2.disposition).GetY()/(v1.disposition-v2.disposition).Distance());
    return new_vector;
    //return (v2.disposition-v1.disposition)*std::max((v1.disposition-v2.disposition).Distance(), 0.)/l_spring_*(-0.1); //CONST
}

void Graph::DirectedForce(size_t epsilon, size_t max_iterations){
    size_t iter_count = 0;
    std::vector<Vertex> new_verticies = verticies_;
    for (size_t i = 0; i < verticies_count_; ++i){
        Vector new_vector(rand()%100, rand()%100);
        new_verticies[i].position = new_vector;
        new_verticies[i].disposition = new_vector;
    }
    for (size_t i = 0; i < new_verticies.size(); ++i){
        std::cout << "vertex" << new_verticies[i].num_ << '\n';
        std::cout << "x: " << new_verticies[i].position.GetX() << ' ' << "y: " << new_verticies[i].position.GetY() << '\n';
    }
    size_t stop_iter = 10;
    while (iter_count < max_iterations){ //&& (max(abs(force(iter_count))) > epsilon)
        double totalDisplacement = 0;
        for (size_t i = 0; i < verticies_count_; ++i){
            //calculate force of i vertex
            Vertex copy_vertex = new_verticies[i];
            Vector calc_force(0,0);
            for (size_t j = 0; j < verticies_count_; ++j){
                if (i == j) continue;
                Vector dist = new_verticies[i].position - new_verticies[j].position;
                //copy_vertex.disposition = copy_vertex.disposition + (RepulsiveForce(copy_vertex, new_verticies[j])*(dist/dist.Distance()));
                Vector f = RepulsiveForce(copy_vertex, new_verticies[j]);
                calc_force = calc_force + RepulsiveForce(copy_vertex, new_verticies[j]);
                if (abs(f.GetX())>100000){
                    std::cout << "repulsive:\n";
                    std::cout << copy_vertex.disposition.GetX() << ' ' << copy_vertex.disposition.GetY() << '\n';
                    std::cout << new_verticies[j].disposition.GetX() << ' ' << new_verticies[j].disposition.GetY() << '\n';
                    std::cout << "x: " << calc_force.GetX() << ' ' << "y: " << calc_force.GetY() << '\n';
                }
                
                //copy_vertex.disposition = copy_vertex.disposition + (RepulsiveForce(copy_vertex, new_verticies[j])*(dist/dist.Distance()));
            }
            for (size_t j = 0; j < copy_vertex.next_.size(); ++j){
                Vector dist = copy_vertex.position - copy_vertex.next_[j]->position;
                //copy_vertex.disposition = copy_vertex.disposition - AttactiveForce(copy_vertex, *copy_vertex.next_[j]);
                //copy_vertex.next_[j]->disposition = copy_vertex.next_[j]->disposition + AttactiveForce(copy_vertex, *copy_vertex.next_[j]);
                //std::cout << "attactive:\n";
                //std::cout << "x: " << calc_force.GetX() << ' ' << "y: " << calc_force.GetY() << '\n';
                Vector f = AttactiveForce(copy_vertex, new_verticies[j]);
                calc_force = calc_force + AttactiveForce(copy_vertex, *copy_vertex.next_[j]);
                if (abs(f.GetX())>100000){
                    std::cout << "attactive:\n";
                    std::cout << copy_vertex.disposition.GetX() << ' ' << copy_vertex.disposition.GetY() << '\n';
                    std::cout << new_verticies[j].disposition.GetX() << ' ' << new_verticies[j].disposition.GetY() << '\n';
                    std::cout << "x: " << calc_force.GetX() << ' ' << "y: " << calc_force.GetY() << '\n';
                }
            }
            copy_vertex.velocity = (calc_force) * damping_; //copy_vertex.velocity 
            copy_vertex.disposition = copy_vertex.disposition + copy_vertex.velocity;
            if (copy_vertex.disposition.GetX()<11){
                copy_vertex.disposition.SetX(11);
            }
            if (copy_vertex.disposition.GetY()<11){
                copy_vertex.disposition.SetY(11);
            }
            if (copy_vertex.disposition.GetX()>1408-11){
                copy_vertex.disposition.SetX(1408-11);
            }
            if (copy_vertex.disposition.GetY()>939-11){
                copy_vertex.disposition.SetY(939-11);
            }
            new_verticies[i] = copy_vertex;
            //std::cout << "x: " << calc_force.GetX() << ' ' << "y: " << calc_force.GetY() << '\n';
        }
        for (size_t i = 0; i < verticies_count_; ++i){
            //change coordinates using cool coeff
            Vertex copy_vertex = new_verticies[i];
            totalDisplacement += (copy_vertex.position-copy_vertex.disposition).Distance();
            copy_vertex.position = copy_vertex.disposition;
            new_verticies[i] = copy_vertex;
        }
        iter_count++;
        if (totalDisplacement<10) --stop_iter;
        if (stop_iter==0) break;
    }
    int minX = new_verticies[0].disposition.GetX();
    int minY = new_verticies[0].disposition.GetY();
    for (size_t i = 0; i < new_verticies.size(); ++i){
        minX = std::min(minX, new_verticies[i].position.GetX());
        minY = std::min(minY, new_verticies[i].position.GetY());
    }
    Vector vector_shift(-minX+11, -minY+11);
    for (size_t i = 0; i < new_verticies.size(); ++i){
        std::cout << "vertex" << new_verticies[i].num_ << '\n';
        new_verticies[i].position = new_verticies[i].position + vector_shift;
        std::cout << "x: " << new_verticies[i].position.GetX() << ' ' << "y: " << new_verticies[i].position.GetY() << '\n';
        verticies_[i] = new_verticies[i];
    }
}
