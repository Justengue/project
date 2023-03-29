//
//  graph.hpp
//  Graph
//
//  Created by Nicolas Vougny on 11/03/2022.
//

#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

#define INF 2 << 22

class Vertex{
    
protected:
    uint32_t id;
    double longitude;
    double latitude;
    double weight = INF;
    double estimate = 0;
    
public:
    Vertex(const uint32_t k, const double lo, const double la) : id(k), longitude(lo), latitude(la) {}
    Vertex(const Vertex &v){
        id = v.id;
        longitude = v.longitude;
        latitude = v.latitude;
        weight = v.weight;
        estimate = v.estimate;
    }
    Vertex() {}

    uint32_t prev;
    
    uint32_t getId(){ return id; }
    double getLong() { return longitude; }
    double getLat() { return latitude; }
    double getW() { return weight; }
    void setW(const double w){ weight = w; }
    double getE(){ return estimate; }
    void setE(const double e){ estimate = e; }

    friend bool operator==(const Vertex v1, const Vertex v2){

        return (v1.id == v2.id && v1.latitude == v2.latitude && v1.longitude == v2.longitude); //&& v1.weight == v2.weight);
    }

    Vertex &operator=(const Vertex &v){

        id = v.id;
        longitude = v.longitude;
        latitude = v.latitude;
        weight = v.weight;
        estimate = v.estimate;

        return *this;
    }
};

class Edge {
    
protected:
    int v1Id;
    int v2Id;
    double dist;
    
public:
    Edge(int v1, int v2, double d) : v1Id(v1), v2Id(v2), dist(d) {}
    
    uint32_t getV1Id(){ return v1Id; }
    uint32_t getV2Id(){ return v2Id; }
    double getDist(){ return dist; }

    friend bool operator==(Edge e1, Edge e2){

        return(e1.getV1Id() == e2.getV1Id() && e1.getV2Id() == e2.getV2Id() && e1.getDist() == e2.getDist());
    }
};


class Graph {
protected:
    std::map<int, Vertex> vertList;
    std::vector<Edge> edgeList;
    
public:
    Graph(const std::string fileName);

    Edge getEdge(Vertex v1, Vertex v2);
    
    void neighbors(const Vertex v, std::vector<Vertex> &list);
    void bfs(uint32_t vstart, uint32_t vstop);
    void dijkstra(uint32_t vstart, uint32_t vstop);
    void astar(uint32_t vstart, uint32_t vstop);
};

