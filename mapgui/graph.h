#pragma once

#include "edgeitem.h"
#include "vertexitem.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#define INF 2 << 22

class Graph {
protected:
    std::map<int, VertexItem> vertexList;
    std::vector<EdgeItem> edgeList;

public:
    Graph(const std::string file);

    Edge getEdge(Vertex v1, Vertex v2);

    void neighbors(const Vertex v, std::vector<Vertex> &list);
    std::vector<uint32_t> bfs(uint32_t vstart, uint32_t vstop);
    std::vector<uint32_t> dijkstra(uint32_t vstart, uint32_t vstop);
    std::vector<uint32_t> astar(uint32_t vstart, uint32_t vstop);
};
