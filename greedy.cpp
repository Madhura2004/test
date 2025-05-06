#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

#define INF INT_MAX

void primMST(vector<vector<int>> &graph, int V) 
{
    vector<int> key(V, INF);         // Minimum weight edge to a vertex
    vector<bool> mstSet(V, false);   // Included in MST?
    vector<int> parent(V, -1);       // Store MST

    key[0] = 0; // Start from first vertex

    for (int count = 0; count < V - 1; ++count) 
    {
        // Pick min key vertex not in MST
        int u = -1, minKey = INF;
        for (int v = 0; v < V; ++v) 
        {
            if (!mstSet[v] && key[v] < minKey) 
            {
                minKey = key[v];
                u = v;
            }
        }

        mstSet[u] = true;

        // Update adjacent vertices
        for (int v = 0; v < V; ++v) 
        {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) 
            {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print MST
    cout << "\nPrim's MST:\n";
    int totalWeight = 0;
    for (int i = 1; i < V; ++i) 
    {
        cout << parent[i] << " - " << i << " : " << graph[i][parent[i]] << "\n";
        totalWeight += graph[i][parent[i]];
    }
    cout << "Total Weight: " << totalWeight << "\n";
}

// ========== Kruskal's Algorithm ==========""""""""""""""""""""""""""""""""""
struct Edge 
{
    int src, dest, weight;
};

bool cmp(Edge a, Edge b) 
{
    return a.weight < b.weight;
}

int findSet(int u, vector<int> &parent) 
{
    if (parent[u] != u)
        parent[u] = findSet(parent[u], parent); // Path compression
    return parent[u];
}

void unionSet(int u, int v, vector<int> &parent, vector<int> &rank) 
{
    u = findSet(u, parent);
    v = findSet(v, parent);
    if (rank[u] < rank[v])
        parent[u] = v;
    else if (rank[v] < rank[u])
        parent[v] = u;
    else {
        parent[v] = u;
        rank[u]++;
    }
}

void kruskalMST(vector<Edge> &edges, int V) 
{
    sort(edges.begin(), edges.end(), cmp);

    vector<int> parent(V), rank(V, 0);
    for (int i = 0; i < V; ++i)
        parent[i] = i;

    vector<Edge> result;
    int totalWeight = 0;

    for (Edge e : edges)
    {
        int u_set = findSet(e.src, parent);
        int v_set = findSet(e.dest, parent);

        if (u_set != v_set) 
        {
            result.push_back(e);
            totalWeight += e.weight;
            unionSet(u_set, v_set, parent, rank);
        }
    }

    // Print MST
    cout << "\nKruskal's MST:\n";
    for (Edge e : result)
        cout << e.src << " - " << e.dest << " : " << e.weight << "\n";
    cout << "Total Weight: " << totalWeight << "\n";
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> adjMatrix(V, vector<int>(V, 0));
    vector<Edge> edges;

    cout << "Enter edges (src dest weight):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;  
        edges.push_back({u, v, w});
    }

    primMST(adjMatrix, V);
    kruskalMST(edges, V);

    return 0;
}

// auto end = chrono::high_resolution_clock::now();
// chrono::duration<double> duration = end - start;
// cout << "Time Complexity of Prim's Algorithm: O(V^2) => Execution Time: " << duration.count() << " seconds.\n";
