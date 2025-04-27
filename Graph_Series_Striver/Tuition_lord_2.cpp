#include <bits/stdc++.h>
using namespace std;

// max-heap : priority_queue<int> pq;
// min-heap : priority_queue<int, vector<int>, greater<int>> pq;

// greater<pair<int, int>> →
// This says:
// When comparing two pairs, smaller comes first.
// First compare by first, and if equal, compare by second.
// list of (totalCost, node) pairs.

class Solution {
public:
    void findPath(int K, int n, vector<vector<int>>& edges, int S, int D) {
        vector<pair<int, pair<int, int>>> adj[n + 1];
        for (auto it : edges) {
            int u = it[0], v = it[1], t = it[2], c = it[3];
            adj[u].push_back({v, {t, c}});
            adj[v].push_back({u, {t, c}});
        }

        priority_queue<pair<int, pair<int, vector<int>>>, 
                       vector<pair<int, pair<int, vector<int>>>>, 
                       greater<pair<int, pair<int, vector<int>>>>> pq;
                       
        vector<int> minCost(n + 1, INT_MAX);

        pq.push({0, {0, {S}}}); // {totalCost, {totalTime, path}}
        minCost[S] = 0;

        while (!pq.empty()) {
            int totalCost = pq.top().first;
            int totalTime = pq.top().second.first;
            vector<int> path = pq.top().second.second;
            int u = path.back();
            pq.pop();
            
            if (u == D) {
                for (int i = 0; i < path.size(); i++) {
                    cout << path[i];
                    if (i != path.size() - 1) cout << "->";
                }
                cout << " " << totalTime << " " << totalCost << endl;
                return;
            }
            
            if (totalCost > minCost[u]) continue;
            
            for (auto it : adj[u]) {
                int v = it.first;
                int travelTime = it.second.first;
                int travelCost = it.second.second;
                
                int waitTime = (path.size() > 1) ? 1 : 0; // Wait only if not starting node
                int newTime = totalTime + travelTime + waitTime;
                int opportunityCost = (newTime - totalTime) * K;
                int newCost = totalCost + travelCost + opportunityCost;
                
                if (newCost < minCost[v]) {
                    minCost[v] = newCost;
                    vector<int> newPath = path;
                    newPath.push_back(v);
                    pq.push({newCost, {newTime, newPath}});
                }
            }
        }
        
        cout << "Error" << endl;
    }
};

int main() {
    int K, N, X;
    cin >> K >> N >> X;
    
    vector<vector<int>> edges;
    for (int i = 0; i < X; ++i) {
        int u, v, t, c;
        cin >> u >> v >> t >> c;
        edges.push_back({u, v, t, c});
    }
    
    int S, D;
    cin >> S >> D;
    
    Solution obj;
    obj.findPath(K, N, edges, S, D);

    return 0;
}
