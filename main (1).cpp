//
// GROUPE : BROSSIER COLLIN DESOUSA 29/03/2023
//

#include <cstdlib>
#include <iostream>
#include "graph.hpp"
#include <vector>

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
    
    uint32_t start_id = stoi(start);
    uint32_t end_id = stoi(end);
    vector<uint32_t> path;

    Graph graph(fileName);

    if((start_id != 0 && end_id != 0) && algo == "bfs") path=graph.bfs(start_id, end_id);
    else if((start_id != 0 && end_id != 0) && algo == "dijkstra") path=graph.dijkstra(start_id, end_id);
    else if((start_id != 0 && end_id != 0) && algo == "astar") path=graph.astar(start_id, end_id);
    
   
    // Bfs path 
    for(uint32_t i=0; i<path.size(); i++){
        cout << "chemin : "<< i <<" "<<endl;
        printf("%6d \n", path[path.size()-i-1]);
    }
    
    return EXIT_SUCCESS;
}
