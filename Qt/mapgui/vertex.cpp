#include "vertex.h"
double minLat, maxLat, minLong, maxLong;

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

double Vertex::getX(){
    const double R=6371000;
    const double lambda=M_PI*64.56/180;
    const double phi=M_PI*18.26/180;
    const double R0=R*cos(phi);
    return R0*M_PI*(this->getLong()-lambda)/180;
}

double Vertex::getY(){
    const double R=6371000;
    const double phi=M_PI*18.26/180;
    return R*log(tan(M_PI/4+M_PI*(this->getLat()-phi)/360));
}
