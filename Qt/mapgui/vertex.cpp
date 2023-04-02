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
double Vertex::getX() {
  const double R0 = 6371.0;

  double long_center=minLong+(maxLong-minLong)/2;
  double lat_center=minLat+(maxLat-minLat)/2;
  double xmax = R0*cos(lat_center) * (maxLong - long_center);
  double xmin = R0*cos(lat_center) * (minLong - long_center);
  double ax = 10000.0 / (xmax - xmin);
  double bx = -ax * xmin;
  double x;

  x = ax * R0 * cos(this->getLat()) * (this->getLong() - long_center) + bx;

  return x;
}

double Vertex::getY() {
  const double R0 = 6371.0;

  double lat_center=minLat+(maxLat-minLat)/2;
  double ymax = R0*log(tan((maxLat - lat_center) / 2 + M_PI / 4));
  double ymin = R0*log(tan((minLat - lat_center) / 2 + M_PI / 4));
  double ay = 10000.0 / (ymax - ymin);
  double by = -ay * ymin;
  double y;

  y = ay * R0 * log(tan((this->getLat() - lat_center) / 2 + M_PI / 4)) + by;

  return y;
}
