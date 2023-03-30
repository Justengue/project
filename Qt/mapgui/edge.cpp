#include "edge.h"

Edge::Edge(int v1, int v2, double d) : startId_(v1), endId_(v2), length_(d) {}

uint32_t Edge::getStartId(){ return startId_; }
uint32_t Edge::getEndId(){ return endId_; }
double Edge::getLength(){ return length_; }
