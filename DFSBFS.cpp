#include<iostream>
#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

   public:
    Graph(int V) {
        this->V = V;
        adj = vector<vector<int>>(V);
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    void BFS(int s) {
        vector<bool> visited(V, false);
        queue<int> q;

        q.push(s);
        visited[s] = true;

        while (!q.empty()) {
            int u = q.front();
            cout << u << " ";
            q.pop();

            for (int i = 0; i < adj[u].size(); i++) {
                if (!visited[adj[u][i]]) {
                    visited[adj[u][i]] = true;
                    q.push(adj[u][i]);
                }
            }
        }
    }

    void DFS(int s) {
        vector<bool> visited(V, false);
        stack<int> st;
        st.push(s);
        visited[s] = true;

        while (!st.empty()) {
            int u = st.top();
            cout << u << " ";
            st.pop();

            for (int i = 0; i < adj[u].size(); i++) {
                if (!visited[adj[u][i]]) {
                    visited[adj[u][i]] = true;
                    st.push(adj[u][i]);
                }
            }
        }
    }

    void DFSRecursive(int s, vector<bool> &visited) {
        visited[s] = true;          
        cout << s << " ";

        for (int i = 0; i < adj[s].size(); i++) {
            if (!visited[adj[s][i]]) {
                DFSRecursive(adj[s][i], visited);
            }
        }
    }

    void BFSRecursiveUtil(queue<int>& q, vector<bool>& visited) {
        if (q.empty()) return;

        int u = q.front();
        q.pop();
        cout << u << " ";

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }

        BFSRecursiveUtil(q, visited);
    }

    void BFSRecursive(int s) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[s] = true;
        q.push(s);
        BFSRecursiveUtil(q, visited);
    }
};
int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter the edges (u v) where u and v are vertices connected by an edge:" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Enter the starting vertex for BFS and DFS: ";
    cin >> start;

    cout << "BFS (iterative) starting from vertex " << start << ": ";
    g.BFS(start);
    cout << endl;

    cout << "BFS (recursive) starting from vertex " << start << ": ";
    g.BFSRecursive(start);
    cout << endl;

    cout << "DFS (using stack) starting from vertex " << start << ": ";
    g.DFS(start);
    cout << endl;

    cout << "DFS (recursive) starting from vertex " << start << ": ";
    vector<bool> visited(V, false);
    g.DFSRecursive(start, visited);
    cout << endl;

    return 0;
}
