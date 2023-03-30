//
// Embedded C++
// TEAM : BROSSIER COLLIN DESOUSA 29/03/2023
//

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <deque>
#include <cmath>
#include <vector>
#include "graph.hpp"

#define INF 2 << 22
#define pi 3.14159265359

using namespace std;

Graph::Graph(const string file){
    
    ifstream fin(file, ios::in);
    if(!fin.is_open()){
        perror("File can't be opened");
    }
    else{
        string line;
        int v_counter = 0, e_counter = 0;
        
        while (getline(fin, line)){
            
            stringstream ss(line);
            string c1, c2, c3, c4;
            
            getline(ss, c1,',');
            getline(ss, c2,',');
            getline(ss, c3,',');
            getline(ss, c4,',');
            
            if(c1 == "V"){
                Vertex v(stoi(c2), stod(c3), stod(c4));
                vertexList.insert({stoi(c2), v});
                v_counter ++;
            }
            else if(c1 == "E"){
                Edge e(stoi(c2), stoi(c3), stod(c4));
                edgeList.push_back(e);
                e_counter ++;
            }
        }
        cout << "Graph created from " << file << " : " << v_counter << " vertex and " << e_counter << " edges added." << endl;
    }
    fin.close();
}


// Return the list of all the vertices 
vector<Vertex> Graph::getAllVertices(){

    vector<Vertex> allVertex; 
    for( it=vertexList.begin(); it!=vertexList.end(); it++){
        allVertex.push_back(it->second);
    }

    return allVertex;
}

//Return the min(0), max(1) longitude and min(2), max(3) latitude
vector<double> Graph::MinMaxLongLat(){
    vector<double> MinMaxLongLat={10000000.0,-10000000.0,10000000.0,-10000000.0};
    vector<Vertex> allVertex = getAllVertices();
    for( uint32_t i=0; i<allVertex.size(); i++){
        
        if(allVertex[i].getLong()<MinMaxLongLat[0]) MinMaxLongLat[0]=allVertex[i].getLong();
            
        if(allVertex[i].getLong()>MinMaxLongLat[1]) MinMaxLongLat[1]=allVertex[i].getLong();
                
        if(allVertex[i].getLat()<MinMaxLongLat[2]) MinMaxLongLat[2]=allVertex[i].getLat();
                
        if(allVertex[i].getLat()>MinMaxLongLat[3]) MinMaxLongLat[3]=allVertex[i].getLat();

    }  
    return MinMaxLongLat;  
}


// Return the list of all the edges
vector<Edge> Graph::getAllEdges(){ 
    
    return edgeList;
}

Edge Graph::getEdge(Vertex v1, Vertex v2){

    for(Edge e : edgeList){ 
        if(e.getStartId() == v1.getId() && e.getEndId() == v2.getId()) return e;
    }
    cout << "Error : no edge between these two vertices." << endl;
    Edge e(-1, -1, 0);
    return (e);
}

void Graph::neighbors(Vertex v, vector<Vertex> &list){
    
    //Fullfil a list of neightbor from a vertex

    for(Edge e : edgeList){

        if(e.getStartId() == v.getId()){
            auto it = vertexList.find(e.getEndId());
            list.push_back(it->second);
        }
    }
}

vector<uint32_t> Graph::bfs(uint32_t vstart, uint32_t vstop){
    
    //Container
    deque<Vertex> active_queue;
    vector<Vertex> closed_set;
    vector<Vertex> visited;
    map<uint32_t, pair<uint32_t, double>> next_before; //Map in which will be stored the vertices, their direct precedent and the distance between them

    //Variables
    Vertex vcurrent;
    int visited_vertices = 0;
    bool stop_flag = false;
    double dist;
    
    //We get the two vector thank to the id 
    auto it_va = vertexList.find(vstart);
    auto it_vb = vertexList.find(vstop);
    Vertex v1 = it_va->second;
    Vertex v2 = it_vb->second;

    active_queue.push_back(v1);
    
    while(active_queue.size() != 0){
    
        visited_vertices ++;
        
        vcurrent = active_queue.front();
        active_queue.pop_front();
        closed_set.push_back(vcurrent);
        
        //We stop the while if we find the destination vstop
        if(stop_flag == true){ 
            cout << "A path does exist." << endl;
            break;
        }
        
        vector<Vertex> adjacency_list; //List of the vcurrent's neighbor
        neighbors(vcurrent, adjacency_list);
      
        for(Vertex vnext : adjacency_list){

            //We recove the distance between these to vertices
            dist = getEdge(vcurrent, vnext).getLength();
            
            next_before.insert({vnext.getId(), {vcurrent.getId(), dist}});
            visited.push_back(vnext);
            
            auto it_cs = find(closed_set.begin(), closed_set.end(), vnext); //Search vnext in closed_set
            auto it_aq = find(active_queue.begin(), active_queue.end(), vnext); //Search vnext in active_queue
            
            if(it_cs != closed_set.end()) continue ; //If vnext is in closed_set we continu

            if(it_aq == active_queue.end()){ //If vnext is not present in active_queue we add it
                if(vnext == v2){ //Stop condition
                    stop_flag = true;
                    visited.push_back(vnext);
                    break;
                }
                active_queue.push_back(vnext);
            }
        }
    }

    //If the path between these two vertices doesn't exist
    if(active_queue.size() == 0){
        cout << "There is no path between these two vertices." << endl;
    }

    //Filling list of path and distances
    double total_dist = 0;
    vector<uint32_t> path = {visited.back().getId()};
    vector<double> distances = {0};
    auto it_nb = next_before.find(visited.back().getId());
    uint32_t previous = it_nb->second.first;

    while(previous != v1.getId()){ //Filling the path starting from the end
        total_dist += it_nb->second.second;
        path.push_back(previous);
        distances.push_back(total_dist);

        it_nb = next_before.find(previous);
        previous = it_nb->second.first;
    }

    total_dist += it_nb->second.second;
    path.push_back(v1.getId());
    distances.push_back(total_dist);

    //Display 
    cout << "Total visited vertex : " << visited_vertices << endl;
    cout << "Total vertex on path from start to end : " << path.size() << endl;

    for(uint32_t i = 0; i<path.size(); i++){

        cout << "Vertex[";
        printf("%3d", i+1);
        cout << "] = ";
        printf("%6d", path[path.size()-i-1]);
        cout << ", length = ";
        printf("%9.2f", total_dist - distances[distances.size()-i-1]);
        cout << endl;
    }
    return path;
}

bool weightCompare(Vertex v1, Vertex v2){
    return(v1.getW() < v2.getW());
}

vector<uint32_t> Graph::dijkstra(uint32_t vstart, uint32_t vstop){

    //Containers
    deque<Vertex> active_queue; //Contains active vertices and their weight (for sorting)
    vector<Vertex> closed_set;
    vector<Vertex> visited;
    map<uint32_t, pair<uint32_t, double>> next_before; //Map in which will be stored the vertices, their direct precedent and the distance between them

    //Variables
    Vertex vcurrent;
    int visited_vertices = 0;
    double dist;
    double weight = 0;
     
    //We get the two vector thank to the id 
    auto it_va = vertexList.find(vstart);
    auto it_vb = vertexList.find(vstop);
    Vertex v1 = it_va->second;
    Vertex v2 = it_vb->second;

    v1.setW(0.0);
    active_queue.push_back(v1);
     
    while(active_queue.size() != 0){
     
        visited_vertices ++;
        
        vcurrent = active_queue.front();
        active_queue.pop_front();
        closed_set.push_back(vcurrent);
        
        //We stop the while if we find the destination vstop
        if(vcurrent == v2){ 
            cout << "A path does exist." << endl;
            visited.push_back(vcurrent);
            break;
        }

        vector<Vertex> adjacency_list; //List of vcurrent's neighbor
        neighbors(vcurrent, adjacency_list);
       
        for(Vertex vnext : adjacency_list){

            dist = getEdge(vcurrent, vnext).getLength();

            visited.push_back(vnext);

            auto it_cs = find(closed_set.begin(), closed_set.end(), vnext); //Search vnext in closed_set
            auto it_aq = find(active_queue.begin(), active_queue.end(), vnext);

            if(it_cs != closed_set.end()) continue; //If vnext is in closed-set we continu

            weight = vcurrent.getW() + dist;

            if(it_aq == active_queue.end()){ //If vnext is not in active_queue we add it
                vnext.setW(weight);
                active_queue.push_back(vnext);
                next_before.insert({vnext.getId(), {vcurrent.getId(), dist}});
            }
            else if(weight < vnext.getW()){
                vnext.setW(weight);
            }
            next_before[vnext.getId()] = {vcurrent.getId(), dist};
        }
        sort(active_queue.begin(), active_queue.end(), weightCompare);
    }   
    if(active_queue.size() == 0){
        cout << "There is no path between these two vertices." << endl;
    }

    //Filling list of path and distances
    double total_dist = 0;
    vector<uint32_t> path = {visited.back().getId()};
    vector<double> distances = {0};
    auto it_nb = next_before.find(visited.back().getId());
    uint32_t previous = it_nb->second.first;

    while(previous != v1.getId()){ //We fill the path starting from the end

        total_dist += it_nb->second.second;
        path.push_back(previous);
        distances.push_back(total_dist);

        it_nb = next_before.find(previous);
        previous = it_nb->second.first; 
    }

    total_dist += it_nb->second.second;
    path.push_back(v1.getId());
    distances.push_back(total_dist);

    //Display
    cout << "Total visited vertex : " << visited_vertices << endl;
    cout << "Total vertex on path from start to end : " << path.size() << endl;

    for(uint32_t i = 0; i<path.size(); i++){

        cout << "Vertex[";
        printf("%3d", i+1);
        cout << "] = ";
        printf("%6d", path[path.size()-i-1]);
        cout << ", length = ";
        printf("%9.2f", total_dist - distances[distances.size()-i-1]);
        cout << endl;
    }
    return path;
}

double heuristic_distance_estimator(Vertex v1, Vertex v2){
    double l = v1.getLong()*pi/180;
    double lc = v2.getLong()*pi/180;
    double p = v1.getLat()*pi/180;
    double pc = v2.getLat()*pi/180;
    double r = 6378137;

    double x = r*cos(pc)*(l - lc);
    double y = r*log(tan(((p-pc)/2)+pi/4));

    return sqrt(pow(x,2) + pow(y,2));
}

// the partial sort ensure that the vertex with the smallest estimate
bool estimateSort(Vertex v1, Vertex v2){
    return(v1.getE() < v2.getE());
}

vector<uint32_t> Graph::astar(uint32_t vstart, uint32_t vstop){

    //Containors
    deque<Vertex> active_queue; //Contains active vertices and their weight (for sorting)
    vector<Vertex> closed_set;
    vector<Vertex> visited;
    map<uint32_t, pair<uint32_t, double>> next_before; //Map in which will be stored the vertices, their direct precedent and the distance between them

    //Variables
    Vertex vcurrent;
    int visited_vertices = 0;
    double dist;
    double f = 0;
    double g = 0;
     
    //We retrieve the two vectors from their id
    auto it_va = vertexList.find(vstart);
    auto it_vb = vertexList.find(vstop);
    Vertex v1 = it_va->second;
    Vertex v2 = it_vb->second;

    v1.setW(0.0);
    active_queue.push_back(v1);
     
    while(active_queue.size() != 0){
     
        visited_vertices ++;
        
        vcurrent = active_queue.front();
        active_queue.pop_front();
        closed_set.push_back(vcurrent);
        
        if(vcurrent == v2){ //We stop the loop if we find vstop
            cout << "A path does exist." << endl;
            visited.push_back(vcurrent);
            break;
        }

        vector<Vertex> adjacency_list; //List of direct neighbors of vcurrent
        neighbors(vcurrent, adjacency_list);
       
        for(Vertex vnext : adjacency_list){

            dist = getEdge(vcurrent, vnext).getLength();

            visited.push_back(vnext);

            auto it_cs = find(closed_set.begin(), closed_set.end(), vnext); //Searching for vnext in closed_set
            auto it_aq = find(active_queue.begin(), active_queue.end(), vnext);

            if(it_cs != closed_set.end()) continue; //If vnext is present in closed_set we continue
            g = vcurrent.getW() + dist;
            f = g + heuristic_distance_estimator(vnext, v2);

            if(it_aq == active_queue.end()){ //If vnext is not present in active_queue we add it
                vnext.setW(g);
                vnext.setE(f);
                active_queue.push_back(vnext);
                next_before.insert({vnext.getId(), {vcurrent.getId(), dist}});
            }
            else if(f < vnext.getE()){
                vnext.setW(g);
                vnext.setE(f);
            }
        }
        sort(active_queue.begin(), active_queue.end(), estimateSort);
    }
    if(active_queue.size() == 0){
        cout << "There is no path between these two vertices." << endl;
    }

    //Filling list of path and distances
    double total_dist = 0;
    vector<uint32_t> path = {visited.back().getId()};
    vector<double> distances = {0};
    auto it_nb = next_before.find(visited.back().getId());
    uint32_t previous = it_nb->second.first;

    while(previous != v1.getId()){ //We fill the path starting from the end
        
        total_dist += it_nb->second.second;
        path.push_back(previous);
        distances.push_back(total_dist);

        it_nb = next_before.find(previous);
        previous = it_nb->second.first;
    }

    total_dist += it_nb->second.second;
    path.push_back(v1.getId());
    distances.push_back(total_dist);

    //Affichage :
    cout << "Total visited vertex : " << visited_vertices << endl;
    cout << "Total vertex on path from start to end : " << path.size() << endl;

    for(uint32_t i = 0; i<path.size(); i++){

        cout << "Vertex[";
        printf("%3d", i+1);
        cout << "] = ";
        printf("%6d", path[path.size()-i-1]);
        cout << ", length = ";
        printf("%9.2f", total_dist - distances[distances.size()-i-1]);
        cout << endl;
    }
    return path;
}

