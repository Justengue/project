//
// Embedded C++
// TEAM : BROSSIER COLLIN DESOUSA 29/03/2023
//

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "graph.hpp"
#include <vector>

using namespace std;



int main(int argc, const char * argv[]) {
    
    //Arguments managing 
    string start(argv[2]);
    string end(argv[4]);
    string algo(argv[6]);
    string file(argv[8]);
    
    uint32_t start_id = stoi(start); //start vertex id
    uint32_t end_id = stoi(end); //end vertex id
    vector<uint32_t> path; //path returned by the method

    Graph graph(file);

    //Launching methods from the arguments (algo) passed as parameters
    //Check if the starting point and the ending point are corrects
    if((start_id != 0 && end_id != 0) && algo == "bfs") path=graph.bfs(start_id, end_id); 
    else if((start_id != 0 && end_id != 0) && algo == "dijkstra") path=graph.dijkstra(start_id, end_id);
    else if((start_id != 0 && end_id != 0) && algo == "astar") path=graph.astar(start_id, end_id);
    
    vector<Vertex> allVertex = graph.getAllVertices();
    
    vector<Edge> allEdge = graph.getAllEdges();

    /*
    for(uint32_t i=0; i<15; i++){
        cout<<"X :"<<allVertex[i].getX()<<"\tY :"<<allVertex[i].getY()<<endl;
    }

    cout<<"MinMaxLongLat : "<<minLong<<"\t"<<maxLong<<"\t"<<minLat<<"\t"<<maxLat<<endl;*/

    return EXIT_SUCCESS;
}