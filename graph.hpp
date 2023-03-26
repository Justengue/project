#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Vertex {
private:
    // Define a struct to hold the vertex coordinates
    struct Vertex_d {
        int id;
        double longitude;
        double latitude;
    };
    // Private vector to hold the vertex information
    vector<Vertex_d> vertices;

public:
    //Set the vertices coordinates
    void Set(const int v_id, const double lon, const double lat);

    //Get the size of the vector
    int size_vector() const;

    // Getters for the vertex information
    int GetId(const int i) const;
    double GetLongitude(const int i) const;
    double GetLatitude(const int i) const;

};

class Edge {
private:
    // Define a struct to hold the edge information
    struct Edge_d {
        int start_point;
        int end_point;
        double length;
    };
    // Private vector to hold the edge information
    vector<Edge_d> edges;

public:
    //Set the edges coordinates
    void Set(const int start, const int end, const double len);

    //Get the size of the vector
    int size_vector() const;

    // Getters for the edge information
    int GetStartPoint(const int i) const;
    double GetEndPoint(const int i) const;
    double GetLength(const int i) const;

};
