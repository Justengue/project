#include "vertex.h"

Vertex::Vertex(const uint32_t i, const double la, const double lo) : id_(i), longitude_(lo), latitude_(la) {}
Vertex::Vertex(const Vertex &v){
    id_ = v.id_;
    longitude_ = v.longitude_;
    latitude_ = v.latitude_;
    weight_ = v.weight_;
    estimate_ = v.estimate_;
}

uint32_t Vertex::getId(){ return id_; }
double Vertex::getLong() { return longitude_; }
double Vertex::getLat() { return latitude_; }
double Vertex::getW() { return weight_; }
void Vertex::setW(const double w){ weight_ = w; }
double Vertex::getE(){ return estimate_; }
void Vertex::setE(const double e){ estimate_ = e; }
