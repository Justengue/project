#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>

#define INF 2 << 22

class Vertex{
protected:
    uint32_t id_;
    double longitude_;
    double latitude_;
    double weight_ = INF;
    double estimate_ = 0;

public:
    //Constructors
    Vertex(const uint32_t i, const double lo, const double la);
    Vertex(const Vertex &v);
    Vertex() {}

    uint32_t prev;

    uint32_t getId();
    double getLong();
    double getLat();
    double getW();
    void setW(const double w);
    double getE();
    void setE(const double e);

    //Compare two vertices
    friend bool operator==(const Vertex v1, const Vertex v2){
        return (v1.id_ == v2.id_ && v1.latitude_ == v2.latitude_ && v1.longitude_ == v2.longitude_);
    }

    //Overload of the = operator
    Vertex &operator=(const Vertex &v){
        id_ = v.id_;
        longitude_ = v.longitude_;
        latitude_ = v.latitude_;
        weight_ = v.weight_;
        estimate_ = v.estimate_;

        return *this;
    }
};
