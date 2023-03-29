//
//  main.cpp
//  Graph
//
//  Created by Nicolas Vougny on 11/03/2022.
//

#include <cstdlib>
#include <iostream>
#include "graph.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    //Recuperation commandes
//    for(int i = 1; i<argc+1; i++){
//        string commande(argv[i]);
//        if(commande.compare("--start") == 0){
//            string start(argv[i+1]);
//            vstart_id = stoi(start);
//        }
//        else if (commande.compare("--end") == 0){
//            string end(argv[i+1]);
//            vend_id = stoi(end);
//        }
//        else if (commande.compare("--algo") == 0) algo = argv[i+1];
//        else if (commande.compare("--file") == 0) fileName = argv[i+1];
//    }
    
    string start(argv[2]);
    string end(argv[4]);
    string algo(argv[6]);
    string fileName(argv[8]);
    
    uint32_t vstart_id = stoi(start);
    uint32_t vend_id = stoi(end);

    Graph graph(fileName);

    if((vstart_id != 0 && vend_id != 0) && algo == "bfs") graph.bfs(vstart_id, vend_id);
    else if((vstart_id != 0 && vend_id != 0) && algo == "dijkstra") graph.dijkstra(vstart_id, vend_id);
    else if((vstart_id != 0 && vend_id != 0) && algo == "astar") graph.astar(vstart_id, vend_id);
    
    //graph.bfs(86771, 110636);
    
    return EXIT_SUCCESS;
}
