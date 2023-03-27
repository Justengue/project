#include "graph.cpp"

int main(int argc, char *argv[]) {
    //Define the Graph object
    Graph gr("../Resources/data.csv");
    /*
    // Print the vertex and edge information
    for (int i = 0; i < gr.size_vectorV(); i++) {
        cout << "Vertex " << gr.GetId(i) << ": (" << gr.GetLongitude(i) << ", " << gr.GetLatitude(i) << ")" << endl;
    }
    for (int i = 0; i < gr.size_vectorE(); i++) {
        cout << "Edge " << i << ": (" << gr.GetStartPointId(i) << ", " << gr.GetEndPointId(i) << ", " << gr.GetLength(i) << ")" << endl;
    }
    */

    cout << "main debug" << endl;

    vector<int> path = gr.Bfs(1, 15);

    cout << "main debug 2" << endl;



    cout << "The path you entered is: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}
