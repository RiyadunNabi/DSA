#include <iostream>
#include <vector>
#include <queue> // For priority_queue
#include <climits>
#include <numeric>

using namespace std;

/**
 * @brief Implements a 2-Approximation algorithm for the TSP with Triangle Inequality.
 */
class TspApproximation {
private:
    int V; // Number of vertices
    vector<vector<int>> distMatrix;
    vector<int> mstParent;
    vector<int> tour;
    long long tourCost;

    /**
     * @brief Constructs an MST using Prim's algorithm with a priority queue for efficiency.
     * The MST is stored in the mstParent member variable.
     */
    void primMST_with_PQ() {
        // A min-priority queue to store pairs of {key, vertex}.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> key(V, INT_MAX);      // To store the minimum weight to connect a vertex.
        vector<bool> inMST(V, false);     // To track vertices included in MST.
        mstParent.assign(V, -1);

        // Start with the first vertex.
        int src = 0;
        pq.push({0, src});
        key[src] = 0;

        while (!pq.empty()) {
            // Get the vertex with the smallest key value.
            int u = pq.top().second;
            pq.pop();
            
            // If the vertex is already in the MST, skip it.
            if(inMST[u]) {
                continue;
            }

            inMST[u] = true;

            // Iterate through all adjacent vertices of u.
            for (int v = 0; v < V; ++v) {
                int weight = distMatrix[u][v];

                // If v is not in MST and the edge (u,v) is smaller than the current key of v.
                if (!inMST[v] && weight > 0 && key[v] > weight) {
                    // Update key and parent of v, then push to the priority queue.
                    key[v] = weight;
                    pq.push({key[v], v});
                    mstParent[v] = u;
                }
            }
        }
    }
    
    /**
     * @brief A recursive DFS utility to perform preorder traversal of the MST.
     * @param u The current vertex.
     * @param visited Vector to keep track of visited vertices.
     * @param mstAdj Adjacency list representation of the MST.
     */
    void dfs(int u, vector<bool>& visited, const vector<vector<int>>& mstAdj) {
        visited[u] = true;
        tour.push_back(u);

        for (int v : mstAdj[u]) {
            if (!visited[v]) {
                dfs(v, visited, mstAdj);
            }
        }
    }

    /**
     * @brief Creates a preorder walk from the MST to form the TSP tour.
     */
    void getPreorderWalk() {
        // Build an adjacency list for the MST from the parent array.
        vector<vector<int>> mstAdj(V);
        int root = 0;
        for (int i = 0; i < V; ++i) {
            if (mstParent[i] == -1) {
                root = i;
            } else {
                mstAdj[mstParent[i]].push_back(i);
            }
        }

        // Perform DFS from the root to get the preorder walk.
        vector<bool> visited(V, false);
        tour.clear();
        dfs(root, visited, mstAdj);
        
        // Complete the tour by returning to the starting vertex.
        tour.push_back(tour[0]);
    }

    /**
     * @brief Calculates the total cost of the generated tour.
     */
    void calculateTourCost() {
        tourCost = 0;
        for (size_t i = 0; i < tour.size() - 1; ++i) {
            tourCost += distMatrix[tour[i]][tour[i+1]];
        }
    }

public:
    /**
     * @brief Constructs the TspApproximation solver.
     * @param matrix The V x V distance matrix of the graph.
     */
    TspApproximation(const vector<vector<int>>& matrix) 
        : distMatrix(matrix), V(matrix.size()), tourCost(0) {}

    /**
     * @brief Executes the full 2-approximation algorithm.
     * @return A pair containing the tour cost and the tour itself.
     */
    pair<long long, vector<int>> solve() {
        primMST_with_PQ();
        getPreorderWalk();
        calculateTourCost();
        return {tourCost, tour};
    }
};

// --- Main execution block ---
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int num_vertices;
    cin >> num_vertices;

    if (num_vertices == 0) {
        cout << 0 << endl << endl;
        return 0;
    }

    vector<vector<int>> distance_matrix(num_vertices, vector<int>(num_vertices));
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            cin >> distance_matrix[i][j];
        }
    }

    TspApproximation solver(distance_matrix);
    pair<long long, vector<int>> result = solver.solve();
    
    // Print the total cost
    cout << result.first << endl;

    // Print the tour
    for (size_t i = 0; i < result.second.size(); ++i) {
        cout << result.second[i] << (i == result.second.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
