#include "graph.hpp"

//Vertex
void Vertex::Set(const int v_id, const double lon, const double lat){ 
	id = v_id;
	longitude = lon;
	latitude = lat;
}

//Edge
void Edge::Set(const int start, const int end, const double len){
	startVId = start;
	endVId = end;
	length = len;
}


//Graph
int Graph::size_vectorV() const { return this->vertices.size(); }
int Graph::size_vectorE() const { return this->edges.size(); }

int Graph::GetId(const int i) const { return this->vertices[i].id; }
double Graph::GetLongitude(const int i) const { return this->vertices[i].longitude; }
double Graph::GetLatitude(const int i) const { return this->vertices[i].latitude; }

int Graph::GetStartPointId(const int i) const { return this->edges[i].startVId; }
double Graph::GetEndPointId(const int i) const { return this->edges[i].endVId; }
double Graph::GetLength(const int i) const { return this->edges[i].length; }
void Graph::bfs(const int vstart, const int vend) const {
	
	dqueue<int> active_queue;
	set<int> closed_set;

	// ID of the start vertex
	active_queue.push_end(vstart);

	do {
		// from the current vertex in the front of the queue
		// compute all vertices reachable in 1 step
		auto vcurrent = active_queue.pop_front();

		closed_set.add(vcurrent);
		
		for(vnext in adjacency_list of vcurrent) {
			if (vnext is in closed_set) {
				continue;
			}
			if (vnext is not already in active_queue) {
				active_queue.push_end(vnext);
			}
		}
	 } while (active_queue.size() != 0)
}

}