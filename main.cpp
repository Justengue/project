#include "graph.cpp"

int main() {

    //Define the vertex
    Vertex v;
    //Define the Edge
    Edge e;
    //Define the Graph object
    Graph gr;

    // Define the input file name
    string filename = "../Resources/data.csv";
    // Open the input file
    ifstream infile(filename);

    // Check if the file was opened successfully
    if (!infile.is_open()) {
        cerr << "Error: Could not open input file " << filename << endl;
        return 1;
    }
    // Read the input file line by line
    string line;

    while (getline(infile, line)) {
        // Parse the line using a stringstream
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
            gr.addV(v);
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
            gr.addE(e);
        }

    }
    // Close the input file
    infile.close();
    
    // Print the vertex and edge information
    for (int i = 0; i < gr.size_vectorV(); i++) {
        cout << "Vertex " << gr.GetId(i) << ": (" << gr.GetLongitude(i) << ", " << gr.GetLatitude(i) << ")" << endl;
    }
    for (int i = 0; i < gr.size_vectorE(); i++) {
        cout << "Edge " << i << ": (" << gr.GetStartPoint(i) << ", " << gr.GetEndPoint(i) << ", " << gr.GetLength(i) << ")" << endl;
    }
    



    return EXIT_SUCCESS;
}