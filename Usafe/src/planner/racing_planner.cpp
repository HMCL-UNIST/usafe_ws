
//   Copyright (c) 2022 Ulsan National Institute of Science and Technology (UNIST)
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

//   Authour : Hojin Lee, hojinlee@unist.ac.kr
#include <planner/racing_planner.h>
#include <random>

#define PI 3.14159265358979323846264338


namespace planner{
  
RacingLinePlanner::RacingLinePlanner()    
{
      
  return;  
}

RacingLinePlanner::~RacingLinePlanner()
{}

void RacingLinePlanner::load_map(){
return;
}
void RacingLinePlanner::gen_random_graph(){        
    int V = 9;    
    if(number_of_node > 0){
        g = new planner::Graph(number_of_node);    
    }
    
    // g.addEdge(0, 1, 4);
    // g.addEdge(0, 7, 8);
    // g.addEdge(1, 2, 8);
    // g.addEdge(1, 7, 11);
    // g.addEdge(2, 3, 7);
    // g.addEdge(2, 8, 2);
    // g.addEdge(2, 5, 4);
    // g.addEdge(3, 4, 9);
    // g.addEdge(3, 5, 14);
    // g.addEdge(4, 5, 10);
    // g.addEdge(5, 6, 2);
    // g.addEdge(6, 7, 1);
    // g.addEdge(6, 8, 6);
    // g.addEdge(7, 8, 7); 

    Eigen::MatrixXd rand_mtx = Eigen::MatrixXd::Random(number_of_node,number_of_node);
    Eigen::MatrixXd random_graph = rand_mtx*rand_mtx.transpose();
    random_graph = random_graph.array().abs();    
    Eigen::VectorXd zero_vector = Eigen::VectorXd::Zero(number_of_node);
    random_graph.diagonal() << zero_vector;    
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Random graph has been generated" << std::endl;
    std::cout << random_graph << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    route_graph = random_graph;   
    
    return;    
}

int RacingLinePlanner::get_min_cost_index(std::vector<double> costs,std::vector<bool> sptSet)
{
    // int min = std::INT_MAX
    // int min_index = 0; 
    // for (int v = 0; v < number_of_node; v++){
    //     if (sptSet[v] == false && costs[v] <= min){
    //             min = costs[v], min_index = v; 
    //     }            
    // }        
    // return min_index;


return 2;
}
bool RacingLinePlanner::compute_best_route(int src_idx){        
    std::vector<int> paths_tmp = g->shortestPath(src_idx);    
    if(paths_tmp.size() > 0){
        best_route_idx = paths_tmp;        
        return true;
    }
    return false;
}

void RacingLinePlanner::waypoint_to_graph(){
return; 
}
void RacingLinePlanner::compute_edge_cost(){
    return ;
}

// Allocates memory for adjacency list
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair>[V];
}

void Graph::clearEdges(){
    adj = new list<iPair>[V];
}
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}
std::vector<int> Graph::shortestPath(int src)
{   // Start at "src" to Goal "0"  
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/  
    priority_queue<iPair, vector<iPair>, greater<iPair> > pq;
    vector<int> dist(V, INF);
    vector<int> paths(V,0);
    pq.push(make_pair(0, src));
    dist[src] = 0; 
    
    while (!pq.empty()) {        
        int u = pq.top().second;
        pq.pop();
        list<pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {            
            int v = (*i).first;
            int weight = (*i).second;
            if (dist[v] > dist[u] + weight) {                
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                paths[v] = u;                
            }
        }
    }         
    int idx_tmp=  0;
    int while_safe_count = 0;   
    std::vector<int> path_idxs;
    path_idxs.push_back(0);
    while (idx_tmp !=src){    
        idx_tmp = paths[idx_tmp];
        path_idxs.push_back(idx_tmp);
        while_safe_count++;
        if(while_safe_count> V*V){
            path_idxs.clear();
            break;            
        }
    }    
    std::reverse(path_idxs.begin(), path_idxs.end());
    return path_idxs;    

}


}
