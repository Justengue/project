#include "graph.hpp"

//Vertex
void Vertex::Set(const int v_id, const double lon, const double lat){ 
	id = v_id;
	longitude = lon;
	latitude = lat;
}

//Edge
void Edge::Set(const int start, const int end, const double len){
	start_point = start;
	end_point = end;
	length = len;
}


//Graph
void Graph::addV(const Vertex v){
	this->vertices.push_back(v);
}
void Graph::addE(const Edge e){
	this->edges.push_back(e);
}
int Graph::size_vectorV() const { return this->vertices.size(); }
int Graph::size_vectorE() const { return this->edges.size(); }

int Graph::GetId(const int i) const { return this->vertices[i].id; }
double Graph::GetLongitude(const int i) const { return this->vertices[i].longitude; }
double Graph::GetLatitude(const int i) const { return this->vertices[i].latitude; }

int Graph::GetStartPoint(const int i) const { return this->edges[i].start_point; }
double Graph::GetEndPoint(const int i) const { return this->edges[i].end_point; }
double Graph::GetLength(const int i) const { return this->edges[i].length; }


