#pragma once

#include "edge.h"
#include "vertex.h"

using namespace std;

class Graph {
protected:
    map<int, Vertex> vertexList;
    map<int, Vertex>::iterator it;
    vector<Edge> edgeList;

public:
    Graph(const std::string file);

    vector<Vertex> getAllVertices();
    vector<Edge> getAllEdges();
    vector<double> MinMaxLongLat();
    Edge getEdge(Vertex v1, Vertex v2);

    void neighbors(const Vertex v, vector<Vertex> &list);
    vector<uint32_t> bfs(uint32_t vstart, uint32_t vstop);
    vector<uint32_t> dijkstra(uint32_t vstart, uint32_t vstop);
    vector<uint32_t> astar(uint32_t vstart, uint32_t vstop);
};
