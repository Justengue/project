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
vector<int> Graph::Bfs(const int start, const int end) const {
    // Initialize a visited vector to keep track of visited vertices
    vector<bool> visited(this->size_vectorV(), false);

    // Initialize a queue to store vertices to visit
    queue<int> queue;

    // Initialize a vector to store the path from start to end
    vector<int> path;

    // Find the start vertex index
    int start_idx = -1;
    for (int i = 0; i < this->size_vectorV(); i++) {
        if (this->vertices[i].id == start) {
            start_idx = i;
            break;
        }
    }

    // Find the end vertex index
    int end_idx = -1;
    for (int i = 0; i < this->size_vectorV(); i++) {
        if (this->vertices[i].id == end) {
            end_idx = i;
            break;
        }
    }

    // Check if start and end vertices are valid
    if (start_idx == -1 || end_idx == -1) {
        cerr << "Error: Invalid start or end vertex." << endl;
        return path;
    }

    // Mark the start vertex as visited and enqueue it
    visited[start_idx] = true;
    queue.push(start_idx);

    // Keep track of the path from start to end
    vector<int> parent(this->size_vectorV(), -1);
    
    while (!queue.empty()) {
        // Dequeue a vertex from the queue
        int curr_idx = queue.front();
        queue.pop();

        // Check if we reached the end vertex
        if (curr_idx == end_idx) {
            // Build the path from start to end
            int idx = curr_idx;
            while (idx != -1) {
                path.insert(path.begin(), this->vertices[idx].id);
                idx = parent[idx];
            }
            break;
        }

        // Visit all adjacent vertices of the current vertex
        for (int i = 0; i < this->size_vectorE(); i++) {
            if (this->edges[i].startVId == curr_idx) {
                int adj_idx = this->edges[i].endVId;
                if (!visited[adj_idx]) {
                    visited[adj_idx] = true;
                    queue.push(adj_idx);
                    parent[adj_idx] = curr_idx;
                }
            }
            else if (this->edges[i].endVId == curr_idx) {
                int adj_idx = this->edges[i].startVId;
                if (!visited[adj_idx]) {
                    visited[adj_idx] = true;
                    queue.push(adj_idx);
                    parent[adj_idx] = curr_idx;
                }
            }
        }
    }

    return path;
}