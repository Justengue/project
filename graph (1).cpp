//
// GROUPE : BROSSIER COLLIN DESOUSA 29/03/2023
//

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <deque>
#include <cmath>
#include "graph.hpp"

#define INF 2 << 22
#define pi 3.14159265359

using namespace std;

Graph::Graph(const string fileName){
    
    ifstream fin(fileName, ios::in);
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
                vertList.insert({stoi(c2), v});
                v_counter ++;
            }
            else if(c1 == "E"){
                Edge e(stoi(c2), stoi(c3), stod(c4));
                edgeList.push_back(e);
                e_counter ++;
            }
        }
        cout << "Graph created from " << fileName << " : " << v_counter << " vertex and " << e_counter << " edges added." << endl;
    }
    fin.close();
}

Edge Graph::getEdge(Vertex v1, Vertex v2){

    for(Edge e : edgeList){ 
        if(e.getStartId() == v1.getId() && e.getEndId() == v2.getId()) return e;
    }
    cout << "Erreur : pas d'edge entre ces deux vertex." << endl;
    Edge e(-1, -1, 0);
    return (e);
}

void Graph::neighbors(Vertex v, vector<Vertex> &list){
    
    //Remplit la liste avec les voisins ATTEIGNABLES depuis un certain Vertex

    for(Edge e : edgeList){

        if(e.getStartId() == v.getId()){
            auto it = vertList.find(e.getEndId());
            list.push_back(it->second);
        }
    }
}

vector<uint32_t> Graph::bfs(uint32_t vstart, uint32_t vstop){
    
    //Conteneurs
    deque<Vertex> active_queue;
    vector<Vertex> closed_set;
    vector<Vertex> visited;
    map<uint32_t, pair<uint32_t, double>> next_before; //Map dans laquelle sera stockee les vertex, leur precedent direct et la distance entre eux

    //Variables
    Vertex vcurrent;
    int visited_vertices = 0;
    bool stop_flag = false;
    double dist;
    
    //On recupere les deux vecteurs a partir de leur identifiant
    auto it_va = vertList.find(vstart);
    auto it_vb = vertList.find(vstop);
    Vertex v1 = it_va->second;
    Vertex v2 = it_vb->second;

    active_queue.push_back(v1);
    
    while(active_queue.size() != 0){
    
        visited_vertices ++;
        
        vcurrent = active_queue.front();
        active_queue.pop_front();
        closed_set.push_back(vcurrent);
        
        if(stop_flag == true){ //On arrete la boucle si on trouve vstop
            cout << "A path does exist." << endl;
            break;
        }
        
        vector<Vertex> adjacency_list; //Liste des voisins directs de vcurrent
        neighbors(vcurrent, adjacency_list);
      
        for(Vertex vnext : adjacency_list){

            //On recupere la distance en fonction des deux vertex

            dist = getEdge(vcurrent, vnext).getLength();
            
            next_before.insert({vnext.getId(), {vcurrent.getId(), dist}});
            visited.push_back(vnext);

            //Pour debugger -->
            //cout << "next : " << vnext.getId() << " prev : " << vcurrent.getId() << endl;
            
            auto it_cs = find(closed_set.begin(), closed_set.end(), vnext); //Recherche de vnext dans closed_set
            auto it_aq = find(active_queue.begin(), active_queue.end(), vnext); //Recherche de vnext dans active_queue
            
            if(it_cs != closed_set.end()) continue ; //Si vnext est présent dans closed_set on continue

            if(it_aq == active_queue.end()){ //Si vnext n'est pas présent dans active_queue on l'ajoute
                if(vnext == v2){ //Condition d'arret
                    stop_flag = true;
                    visited.push_back(vnext);
                    break;
                }
                active_queue.push_back(vnext);
            }
        }
    }

    //Si le chemin entre les deux vertex n'existe pas
    if(active_queue.size() == 0){
        cout << "There is no path between these two vertices." << endl;
    }

    //Remplissage liste du chamin et des distances
    double total_dist = 0;
    vector<uint32_t> path = {visited.back().getId()};
    vector<double> distances = {0};
    auto it_nb = next_before.find(visited.back().getId());
    uint32_t previous = it_nb->second.first;

    while(previous != v1.getId()){ //On remplit le chemin en partant de la fin
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

bool isLighter(Vertex v1, Vertex v2){
    return(v1.getW() < v2.getW());
}

vector<uint32_t> Graph::dijkstra(uint32_t vstart, uint32_t vstop){

    //Conteneurs
    deque<Vertex> active_queue; //Contient les vertex actifs et leur poids (pour le tri)
    vector<Vertex> closed_set;
    vector<Vertex> visited;
    map<uint32_t, pair<uint32_t, double>> next_before; //Map dans laquelle sera stockee les vertex, leur precedent direct et la distance entre eux

    //Variables
    Vertex vcurrent;
    int visited_vertices = 0;
    double dist;
    double weight = 0;
     
    //On recupere les deux vecteurs a partir de leur identifiant
    auto it_va = vertList.find(vstart);
    auto it_vb = vertList.find(vstop);
    Vertex v1 = it_va->second;
    Vertex v2 = it_vb->second;

    v1.setW(0.0);
    active_queue.push_back(v1);
     
    while(active_queue.size() != 0){
     
        visited_vertices ++;
        
        vcurrent = active_queue.front();
        active_queue.pop_front();
        closed_set.push_back(vcurrent);
        
        if(vcurrent == v2){ //On arrete la boucle si on trouve vstop
            cout << "A path does exist." << endl;
            visited.push_back(vcurrent);
            break;
        }

        vector<Vertex> adjacency_list; //Liste des voisins directs de vcurrent
        neighbors(vcurrent, adjacency_list);
       
        for(Vertex vnext : adjacency_list){

            dist = getEdge(vcurrent, vnext).getLength();

            visited.push_back(vnext);

            auto it_cs = find(closed_set.begin(), closed_set.end(), vnext); //Recherche de vnext dans closed_set
            auto it_aq = find(active_queue.begin(), active_queue.end(), vnext);

            if(it_cs != closed_set.end()) continue; //Si vnext est présent dans closed_set on continue

            weight = vcurrent.getW() + dist;

            if(it_aq == active_queue.end()){ //Si vnext n'est pas présent dans active_queue on l'ajoute
                vnext.setW(weight);
                active_queue.push_back(vnext);
                next_before.insert({vnext.getId(), {vcurrent.getId(), dist}});
            }
            else if(weight < vnext.getW()){
                vnext.setW(weight);
            }
            next_before[vnext.getId()] = {vcurrent.getId(), dist};
        }
        sort(active_queue.begin(), active_queue.end(), isLighter);
    }
    if(active_queue.size() == 0){
        cout << "There is no path between these two vertices." << endl;
    }

    //Remplissage liste du chemin et des distances
    double total_dist = 0;
    vector<uint32_t> path = {visited.back().getId()};
    vector<double> distances = {0};
    auto it_nb = next_before.find(visited.back().getId());
    uint32_t previous = it_nb->second.first;

    while(previous != v1.getId()){ //On remplit le chemin en partant de la fin
        //cout << previous << endl;
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

double hdEstimator(Vertex v1, Vertex v2){
    double l = v1.getLong()*pi/180;
    double lc = v2.getLong()*pi/180;
    double p = v1.getLat()*pi/180;
    double pc = v2.getLat()*pi/180;
    double r = 6378137;

    double x = r*cos(pc)*(l - lc);
    double y = r*log(tan(((p-pc)/2)+pi/4));

    return sqrt(pow(x,2) + pow(y,2));
}

bool estimateSort(Vertex v1, Vertex v2){
    return(v1.getE() < v2.getE());
}

vector<uint32_t> Graph::astar(uint32_t vstart, uint32_t vstop){

    //Conteneurs
    deque<Vertex> active_queue; //Contient les vertex actifs et leur poids (pour le tri)
    vector<Vertex> closed_set;
    vector<Vertex> visited;
    map<uint32_t, pair<uint32_t, double>> next_before; //Map dans laquelle sera stockee les vertex, leur precedent direct et la distance entre eux

    //Variables
    Vertex vcurrent;
    int visited_vertices = 0;
    double dist;
    double f = 0;
    double g = 0;
     
    //On recupere les deux vecteurs a partir de leur identifiant
    auto it_va = vertList.find(vstart);
    auto it_vb = vertList.find(vstop);
    Vertex v1 = it_va->second;
    Vertex v2 = it_vb->second;

    v1.setW(0.0);
    active_queue.push_back(v1);
     
    while(active_queue.size() != 0){
     
        visited_vertices ++;
        
        vcurrent = active_queue.front();
        active_queue.pop_front();
        closed_set.push_back(vcurrent);
        
        if(vcurrent == v2){ //On arrete la boucle si on trouve vstop
            cout << "A path does exist." << endl;
            visited.push_back(vcurrent);
            break;
        }

        vector<Vertex> adjacency_list; //Liste des voisins directs de vcurrent
        neighbors(vcurrent, adjacency_list);
       
        for(Vertex vnext : adjacency_list){

            dist = getEdge(vcurrent, vnext).getLength();

            //cout << " Nextw : " << weight << " thenw : " << vcurrent.getW() << endl;

            visited.push_back(vnext);

            auto it_cs = find(closed_set.begin(), closed_set.end(), vnext); //Recherche de vnext dans closed_set
            auto it_aq = find(active_queue.begin(), active_queue.end(), vnext);

            if(it_cs != closed_set.end()) continue; //Si vnext est présent dans closed_set on continue

            g = vcurrent.getW() + dist;
            f = g + hdEstimator(vnext, v2);

            if(it_aq == active_queue.end()){ //Si vnext n'est pas présent dans active_queue on l'ajoute
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

    //Remplissage liste du chemin et des distances
    double total_dist = 0;
    vector<uint32_t> path = {visited.back().getId()};
    vector<double> distances = {0};
    auto it_nb = next_before.find(visited.back().getId());
    uint32_t previous = it_nb->second.first;

    while(previous != v1.getId()){ //On remplit le chemin en partant de la fin
        //cout << previous << endl;
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

