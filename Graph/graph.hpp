//
// Embedded C++
// TEAM : BROSSIER COLLIN DESOUSA 29/03/2023
//

#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <cmath>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#define INF 2 << 22

extern double minLong,maxLong,minLat,maxLat;

// Creation of our class Vertex 
// This class contain vertices elements : id, longitude, latitude
class Vertex{
    
protected:
    uint32_t id;
    double longitude;
    double latitude;
    double weight = INF;
    double estimate = 0;
    
public:
    //Constructors
    Vertex(const uint32_t i, const double lo, const double la) : id(i), longitude(lo), latitude(la) {}
    Vertex(const Vertex &v){
        id = v.id;
        longitude = v.longitude;
        latitude = v.latitude;
        weight = v.weight;
        estimate = v.estimate;
    }
    Vertex() {}
    
    uint32_t getId(){ return id; }
    double getLong() { return longitude; }
    double getLat() { return latitude; }
    double getW() { return weight; }
    void setW(const double w){ weight = w; }
    double getE(){ return estimate; }
    void setE(const double e){ estimate = e; }


    double getX(){
        const double R=6371000;
        const double lambda=M_PI*64.56/180; 
        const double phi=M_PI*18.26/180;
        const double R0=R*cos(phi);
        return R0*M_PI*(this->getLong()-lambda)/180;
    }

    double getY(){
        const double R=6371000;  
        const double phi=M_PI*18.26/180;
        return R*log(tan(M_PI/4+M_PI*(this->getLat()-phi)/360));
    }


    /*
    double getX(){
        
        const double R0 = 6371.0;
        
        double long_center=minLong+(maxLong-minLong)/2;
        double lat_center=minLat+(maxLat-minLat)/2;
        double xmax = R0*cos(lat_center) * (maxLong - long_center);
        double xmin = R0*cos(lat_center) * (minLong - long_center);
        double ax = 1000.0 / (xmax - xmin);
        double bx = -ax * xmin;
        double x;

        x = ax * R0 * cos(this->getLat()) * (this->getLong() - long_center) + bx;
    
        return x;
    }

    double getY(){
    
        const double R0 = 6371.0;

        double lat_center=minLat+(maxLat-minLat)/2;
        double ymax = R0*log(tan((maxLat - lat_center) / 2 + M_PI / 4));
        double ymin = R0*log(tan((minLat - lat_center) / 2 + M_PI / 4));
        double ay = 1000.0 / (ymax - ymin);
        double by = -ay * ymin;
        double y;

        y = ay * R0 * log(tan((this->getLat() - lat_center) / 2 + M_PI / 4)) + by;

        return y;
    }*/


    //Compare two vertices
    friend bool operator==(const Vertex v1, const Vertex v2){

        return (v1.id == v2.id && v1.latitude == v2.latitude && v1.longitude == v2.longitude);
    }

    //Overload of the = operator
    Vertex &operator=(const Vertex &v){

        id = v.id;
        longitude = v.longitude;
        latitude = v.latitude;
        weight = v.weight;
        estimate = v.estimate;

        return *this;
    }
};


// Creation of our class Edge
// This class contain edges elements : startID, endID, length
class Edge {
    
protected:
    int startId;
    int endId;
    double length;
    
public:
    //Constructor
    Edge(int v1, int v2, double d) : startId(v1), endId(v2), length(d) {}
    
    uint32_t getStartId(){ return startId; }
    uint32_t getEndId(){ return endId; }
    double getLength(){ return length; }

    //Compare two edges
    friend bool operator==(Edge e1, Edge e2){

        return(e1.getStartId() == e2.getStartId() && e1.getEndId() == e2.getEndId() && e1.getLength() == e2.getLength());
    }
};


class Graph {
protected:
    std::map<int, Vertex> vertexList;
    std::map<int, Vertex>::iterator it;
    std::vector<Edge> edgeList;
    
public:
    Graph(const std::string file);

    std::vector<Vertex> getAllVertices();

    std::vector<Edge> getAllEdges();
    void MinMaxLongLat();
    Edge getEdge(Vertex v1, Vertex v2);
    
    void neighbors(const Vertex v, std::vector<Vertex> &list);
    std::vector<uint32_t> bfs(uint32_t vstart, uint32_t vstop);
    std::vector<uint32_t> dijkstra(uint32_t vstart, uint32_t vstop);
    std::vector<uint32_t> astar(uint32_t vstart, uint32_t vstop);
};