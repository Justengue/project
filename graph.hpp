#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

class Vertex {
    public:
        // Define a struct to hold the vertex coordinates
        int id;
        double longitude;
        double latitude;
    
        //Set the vertices coordinates
        void Set(const int v_id, const double lon, const double lat);
};

class Edge {
    public:
        int startVId;
        int endVId;
        double length;

        //Set the edges coordinates
        void Set(const int start, const int end, const double len);        
};

class Graph {
    private:
        vector<Vertex> vertices;
        vector<Edge> edges;
    public:
        Graph(string filename) {
            Vertex v;
            Edge e;
            // Open the input file
            ifstream infile(filename);
            if (!infile.is_open()) {
                cerr << "Error: Could not open input file " << filename << endl;
            }
            string line;

            while (getline(infile, line)) {
                stringstream ss(line);
                string token;
                getline(ss,token, ',');

                if(token=="V"){
                    // Read the first token as the vertex ID
                    int id_v;
                    getline(ss, token, ',');
                    id_v=stoi(token);
                    // Read the second token as the longitude
                    double longitude;
                    getline(ss, token, ',');
                    longitude = stod(token);
                    // Read the third token as the latitude
                    double latitude;
                    getline(ss, token, ',');
                    latitude = stod(token);
                    // Add the vertex information to the vertices vector
                    v.Set(id_v, longitude, latitude);
                    this->vertices.push_back(v);
                }

                if(token=="E"){
                // Read the remaining tokens as edges
                    // Parse the edge information
                    int start_vertex;
                    getline(ss, token, ',');
                    start_vertex = stoi(token);

                    int end_vertex;
                    getline(ss, token, ',');
                    end_vertex = stoi(token);

                    double length;
                    getline(ss, token, ',');
                    length = stod(token);

                    // Add the edge information to the edges vector
                    //edges.push_back({start_vertex, end_vertex, length});
                    e.Set(start_vertex, end_vertex, length);
                    this->edges.push_back(e);
                }

            }
            // Close the input file
            infile.close();

        }
        
        //Get the size of the vector
        int size_vectorV() const;
        int size_vectorE() const;
        //Vertices informations
        int GetId(const int i) const;
        double GetLongitude(const int i) const;
        double GetLatitude(const int i) const;
        //Edges informations
        int GetStartPointId(const int i) const;
        double GetEndPointId(const int i) const;
        double GetLength(const int i) const;
        //Breadth First Search algorithm
        vector<int> BFS(const int start, const int end) const {
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
};