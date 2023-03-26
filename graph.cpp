#include "graph.hpp"

void Vertex::Set(const int v_id, const double lon, const double lat){ vertices.push_back({v_id, lon, lat}); }
int Vertex::size_vector() const { return vertices.size(); }
int Vertex::GetId(const int i) const { return vertices[i].id; }
double Vertex::GetLongitude(const int i) const { return vertices[i].longitude; }
double Vertex::GetLatitude(const int i) const { return vertices[i].latitude; }

void Edge::Set(const int start, const int end, const double len){ edges.push_back({start, end, len}); }
int Edge::size_vector() const{ return edges.size(); }
int Edge::GetStartPoint(const int i) const { return edges[i].start_point; }
double Edge::GetEndPoint(const int i) const { return edges[i].end_point; }
double Edge::GetLength(const int i) const { return edges[i].length; }