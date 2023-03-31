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

vector<double> XY(Graph graph, vector<Vertex> &allVertex){
    vector<double> xy_;
    vector<double> MinMaxLongLat = graph.MinMaxLongLat();
    const double R0 = 6371.0;
    double lat_center=MinMaxLongLat[2]+(MinMaxLongLat[3]-MinMaxLongLat[2])/2;
    double lat_max=MinMaxLongLat[3];
    double lat_min=MinMaxLongLat[2];
    double long_center=MinMaxLongLat[0]+(MinMaxLongLat[1]-MinMaxLongLat[0])/2;
    double long_max=MinMaxLongLat[1];
    double long_min=MinMaxLongLat[0];
    double xmax = R0*cos(lat_center) * (long_max - long_center);
    double xmin = R0*cos(lat_center) * (long_min - long_center);
    double ymax = R0*log(tan((lat_max - lat_center) / 2 + M_PI / 4));
    double ymin = R0*log(tan((lat_min - lat_center) / 2 + M_PI / 4));
    double ax = 1000.0 / (xmax - xmin);
    double ay = 1000.0 / (ymax - ymin);
    double bx = -ax * xmin;
    double by = -ay * ymin;
    double x,y;

    for(uint32_t i=0; i<allVertex.size(); i++){
        x = ax * R0 * cos(allVertex[i].getLat()) * (allVertex[i].getLong() - long_center) + bx;
        y = ay * R0 * log(tan((allVertex[i].getLat() - lat_center) / 2 + M_PI / 4)) + by;
        xy_.push_back(x);
        xy_.push_back(y);
    }
    return xy_;
}


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
    
   
    // Check the return path by displaying it 
    for(uint32_t i=0; i<path.size(); i++){
        cout << "chemin : "<< i <<" : ";
        printf("%6d \n", path[path.size()-i-1]);
    }
    
    vector<Vertex> allVertex = graph.getAllVertices();
    
    vector<Edge> allEdge = graph.getAllEdges();

    vector<double> MinMaxLongLat = graph.MinMaxLongLat();

    for(uint32_t i=0; i<MinMaxLongLat.size(); i++){
        cout << "MinMaxLongLat : "<< MinMaxLongLat[i] <<" "<<endl;
    }

    vector<double> xy_=XY(graph,allVertex);
    
    for(uint32_t i=0; i<xy_.size(); i++){
        if(i%2==0){
            cout<<"X :"<<xy_[i];
        }
        else {cout<<"\tY :"<<xy_[i]<<endl;}
    }
    

    return EXIT_SUCCESS;
}
