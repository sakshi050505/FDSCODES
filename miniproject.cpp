/*
Name : SAKSHI SANDEEP CHAVAN
Roll No : 68
PRN No : F23112081
Class : SE-II(R-Batch)
*/




#include <iostream>
using namespace std;

#define INF 9999999 // Define an infinite value

// Structure to represent an edge for Kruskal's algorithm
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find in Kruskal's algorithm
struct Subset {
    int parent, rank;
};

// Function to find the vertex with the minimum key value in Prim's algorithm
int minKey(int key[], bool mstSet[], int V) {
    int min = INF, minIndex;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the constructed MST for Prim's algorithm
void printMSTPrim(int parent[], int **graph, int V) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
}

// Prim's algorithm to find the MST
void primMST(int **graph, int V) {
    int parent[100]; // Array to store the constructed MST
    int key[100]; // Key values used to pick minimum weight edge
    bool mstSet[100]; // To represent set of vertices included in MST

    // Initialize all keys as infinite and mstSet[] as false
    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    // First vertex key is 0 so that it's picked first
    key[0] = 0;
    parent[0] = -1; // First node is the root of the MST

    // The MST will have V-1 edges
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex not yet included in the MST
        int u = minKey(key, mstSet, V);
        mstSet[u] = true; // Add the picked vertex to the MST set

        // Update key and parent index of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printMSTPrim(parent, graph, V);
}

// Find function for union-find in Kruskal's algorithm
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union function for union-find in Kruskal's algorithm
void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Function to manually sort edges for Kruskal's algorithm
void sortEdges(Edge edges[], int E) {
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// Function to print the constructed MST for Kruskal's algorithm
void printMSTKruskal(Edge result[], int e) {
    cout << "Edge \tWeight\n";
    for (int i = 0; i < e; i++) {
        cout << result[i].src << " - " << result[i].dest << "\t" << result[i].weight << "\n";
    }
}

// Kruskal's algorithm to find the MST
void kruskalMST(Edge edges[], int E, int V) {
    Edge result[100]; // Store the resulting MST
    int e = 0; // Count of edges in MST
    int i = 0; // Index for sorted edges

    // Sort all the edges in non-decreasing order of weight manually
    sortEdges(edges, E);

    // Create V subsets with single elements
    Subset subsets[100];
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Iterate through all sorted edges
    while (e < V - 1) {
        // Pick the smallest edge
        Edge nextEdge = edges[i++];
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // If including this edge doesn't cause a cycle
        if (x != y) {
            result[e++] = nextEdge;
            Union(subsets, x, y);
        }
    }

    // Print the resulting MST
    printMSTKruskal(result, e);
}

int main() {
    // Number of vertices (Healthcare facilities)
    int V, E;

    cout << "Enter the number of hospitals (nodes): ";
    cin >> V;

    // Dynamically allocate memory for the adjacency matrix
    int **graph = new int *[V];
    for (int i = 0; i < V; i++) {
        graph[i] = new int[V];
    }

    // Input the adjacency matrix (graph) from the user
    cout << "Enter the adjacency matrix for the graph (use 0 for no connection and the weight for connected nodes):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    // Input the number of edges for Kruskal's algorithm
    cout << "Enter the number of edges: ";
    cin >> E;

    // Input the edges for Kruskal's algorithm
    Edge edges[100];
    cout << "Enter the edges in the format (src dest weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    int choice;
    cout << "Choose the algorithm to solve the problem:\n";
    cout << "1. Prim's Algorithm\n";
    cout << "2. Kruskal's Algorithm\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        cout << "\nSolving using Prim's Algorithm:\n";
        primMST(graph, V);
    } else if (choice == 2) {
        cout << "\nSolving using Kruskal's Algorithm:\n";
        kruskalMST(edges, E, V);
    } else {
        cout << "Invalid choice!";
    }

    // Deallocate memory for the graph
    for (int i = 0; i < V; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}