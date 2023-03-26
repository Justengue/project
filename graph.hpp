#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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
        int start_point;
        int end_point;
        double length;

        //Set the edges coordinates
        void Set(const int start, const int end, const double len);        
};


class Graph {
    private:
        vector<Vertex> vertices;
        vector<Edge> edges;
    public:
        void addV(const Vertex v);
        void addE(const Edge e);
        
        //Get the size of the vector
        int size_vectorV() const;
        int size_vectorE() const;

        int GetId(const int i) const;
        double GetLongitude(const int i) const;
        double GetLatitude(const int i) const;

        // Getters for the edge information
        int GetStartPoint(const int i) const;
        double GetEndPoint(const int i) const;
        double GetLength(const int i) const;
};