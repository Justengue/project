#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>

class Edge {
protected:
    int startId_;
    int endId_;
    double length_;

public:
    //Constructor
    Edge(int v1, int v2, double d);

    uint32_t getStartId();
    uint32_t getEndId();
    double getLength();

    //Compare two edges
    friend bool operator==(Edge e1, Edge e2){
        return(e1.getStartId() == e2.getStartId() && e1.getEndId() == e2.getEndId() && e1.getLength() == e2.getLength());
    }
};
