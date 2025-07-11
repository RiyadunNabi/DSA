// #include <iostream>
// #include <vector>
// #include <queue>
// #include <climits>
#include <bits/stdc++.h>
using namespace std;

// Number of vertices in given graph
#define V 6

// Returns true if there is a path from source to sink in residual graph.
// Also fills parent[] to store the path.
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    fill(visited, visited + V, false); //fill() is a standard C++ function from <algorithm>. Purpose: It sets all values in the visited array to false.
    //vector<bool> visited(V, false); //or this one

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                visited[v] = true;
                q.push(v);
                parent[v] = u;
            }
        }
    }
    // If we reached sink in BFS starting from source, then return true
    return visited[t];
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v;

    // Create a residual graph and fill the residual graph with given capacities
    int rGraph[V][V]; // Residual graph
    for (u = 0; u < V; u++){
        for (v = 0; v < V; v++){
            rGraph[u][v] = graph[u][v];
        }
    }

    int parent[V]; // This array is filled by BFS and to store path

    int max_flow = 0; // There is no flow initially

    // Augment the flow while there is path from source to sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edges along the path filled by BFS
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        // update residual capacities of the edges and reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        // Add path flow to overall flow
        max_flow += path_flow;
    }
    // Return the overall flow
    return max_flow;
}

int main() {
    // Example graph from Cormen et al. (2001)
    int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
                      };

    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5) << endl;
    return 0;
}
