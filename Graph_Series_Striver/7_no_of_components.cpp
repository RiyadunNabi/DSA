//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution {
private:
    void dfs(vector<vector<int>>& isConnected, vector<bool> &visited, int node) {
        visited[node] = true;
        for (int i = 0; i < isConnected.size(); ++i) {
            if (isConnected[node][i] == 1 && !visited[i]) {
                dfs(isConnected, visited, i);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                ++cnt;
                dfs(isConnected, visited, i);
            }
        }
        return cnt;
    }
};

//{ Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int V, x;
        cin >> V;

        vector<vector<int>> adj;

        for (int i = 0; i < V; i++)
        {
            vector<int> temp;
            for (int j = 0; j < V; j++)
            {
                cin >> x;
                temp.push_back(x);
            }
            adj.push_back(temp);
        }

        Solution ob;
        cout << ob.findCircleNum(adj) << endl;

        cout << "~" << "\n";
    }
    return 0;
}


/*


class Solution {
    private:
        void dfs(vector<vector<int>>& adjL, vector<bool> &visited, int node) {
            visited[node] = true;
            for (int i : adjL[node]) {
                if (!visited[i]) {
                    dfs(adjL, visited, i);
                }
            }
        }
    
    public:
        int findCircleNum(vector<vector<int>>& isConnected) {
            int n = isConnected.size();
            vector<vector<int>> adjL(n);
            
            for (int i = 0; i < n; ++i) {
                for (int j = i+1; j < n; ++j) {
                    if (isConnected[i][j] == 1) {
                        adjL[i].push_back(j);
                        adjL[j].push_back(i);
                    }
                }
            }
    
            vector<bool> visited(n, false);
            int cnt = 0;
            for (int i = 0; i < n; ++i) {
                if (!visited[i]) {
                    dfs(adjL, visited, i);
                    ++cnt;
                }
            }
            return cnt;
        }
}; 

*/

