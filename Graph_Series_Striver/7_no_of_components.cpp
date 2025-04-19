//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution
{
private:
    void dfs(vector<vector<int>> &adjL, vector<bool> &visited, int node)
    {
        visited[node] = true;
        for (int i : adjL[node])
        {
            if (!visited[i])
            {
                dfs(adjL, visited, i);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size();
        vector<vector<int>> adjL(n + 1);
        vector<vector<int>> adj(isConnected);
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (adj[i][j] == 1)
                {
                    adjL[i + 1].push_back(j + 1);
                    adjL[j + 1].push_back(i + 1);
                }
            }
        }

        vector<bool> visited(n + 1, false);
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                cnt++;
                // visited[i]=true;
                dfs(adjL, visited, i);
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
