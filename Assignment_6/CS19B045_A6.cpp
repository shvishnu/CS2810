/**************************************************************************
 *  
 *  File:    CS19B045_A6.cpp
 *
 *  Purpose:    Implementation of SSP using Priority Queue
 *
 *  Author:    Vishnu
 *
 *  Created:    Mon 22-March-2021 13:58:36
 *
 *  Last Modified:    Tue 23-March-2021 18:14:56
 *
 *  Changes:        -
 *
 **************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

const int INF = INT32_MAX;

template <class T> class Graph {

    public:
        Graph(int);
        ~Graph();
        void AddV();
        void AddE(int, int, T);
        void DelE(int, int);
        void BFS(int);
        void SSP(int);

    private:
        vector<vector<pair<int, T>>> adjList;
        int numVer;
};

template <class T> 
Graph<T>:: Graph(int n) {                                           // Constructor with one argument
    numVer = n;
    adjList.resize(numVer);
}

template <class T> 
Graph<T>:: ~Graph() {                                      // Destructor
    for(int i = 0; i < numVer; i++) {
        adjList[i].clear();
    }
    adjList.clear();
}

template <class T> 
void Graph<T>:: AddV() {                           
    numVer++;
    adjList.resize(numVer);             // Adding the new vertex as number numVer-1
}

template <class T>
void Graph<T>:: AddE(int u, int v, T w) {
    if(u >= numVer || v >= numVer) {        // Check if the vertex is valid
        cerr << "Invalid Vertex\n";
        return;
    }
    adjList[u].push_back({v, w});           // Add edge
    adjList[v].push_back({u, w});
}

template <class T>
void Graph<T>:: DelE(int u, int v) {
    if(u >= numVer || v >= numVer) {        // Chacking if the vertices are valid
        cerr << "Invalid Vertex\n";
        return;
    }
    bool ch1 = 0, ch2 = 0;
    for(auto p = adjList[u].begin(); p != adjList[u].end(); p++) {
        if((*p).first == v) {
            adjList[u].erase(p);        // Remove b from adjacency list of a
            ch1 = 1;
            break;
        }
    }
    for(auto p = adjList[v].begin(); p != adjList[v].end(); p++) {
        if((*p).first == u) {
            adjList[v].erase(p);        // Remove a from adjacency list of b
            ch2 = 1;
            break;
        }
    }
    if(!(ch1&ch2)) {        // If the edge is not present in either one of adjacency lists
        cerr << "Invalid Edge\n";
    }
}

template <class T>
void Graph<T>:: SSP(int source)          // source is 0 by default
{
    vector<T> dist(numVer, INF);      // stores the distances of each vertex from source

    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> minDist;

    minDist.push({0, source});

    dist[source] = 0;                             // Distance of source from source is zero
    
    while(minDist.size()) {

        pair<T, int> del = minDist.top();        // top() returns the minimum element of the heap
        minDist.pop();
        int delVertex = del.second;                 // The deleted vertex
        for(auto i: adjList[delVertex]) {                  // iterate through the adjacency list of delVertex
            if(i.first != delVertex && dist[delVertex] != INF && i.second + dist[delVertex] < dist[i.first]) {        //Implementation of Dijkstra's alogorithm
                dist[i.first] = dist[delVertex] + i.second;
                minDist.push({dist[i.first], i.first});
            }
        }
    }

    for(int i = 0; i < numVer; i++) {
        cout << dist[i] << " ";            //Printing the distances of the vertices from the source i.e. 0
    }
}

template <class T>
void Graph<T>:: BFS(int x)          // source is 0 by default
{
    queue<pair<T, int>> q;    // bfs queue is implemented using priority queue to give preference to least index
    vector<bool> vis(numVer, 0);

    vis[x] = true;

    q.push({INT32_MIN, x});

	while(!q.empty()) {
        set<pair<T, int>> s;       // To sort vertices in the order of distances
		auto p = q.front();
        x = p.second;
        cout << x << " ";           // Printing the BFS order
        q.pop();
		for(auto y: adjList[x])
        if(!vis[y.first]) {
            vis[y.first] = 1;
            s.insert({y.second, y.first});      // Insert them in the set first to sort
        }

        while(s.size()) {               // set sorts them in the required order
            auto p = *(s.begin());
            q.push(p);                      // Append to the bfs queue
            s.erase(p);
        }
	}
    cout << endl;
}

int main() {
    int n, q;
    cin >> n >> q;
    int a, b, w;
    string s;
    Graph<int> G(n);
    while(q--) {
        cin >> s;
        if(s == "ADDE") {   
            cin >> a >> b >> w;
            G.AddE(a, b, w);
        }
        else if(s == "ADDV") {
            G.AddV();
        }
        else if(s == "DELE") {
            cin >> a >> b;
            G.DelE(a, b);
        }
    }
    for(int i = 0; i < 2; i++) {
        cin >> s >> a;
        s == "BFS"? G.BFS(a): G.SSP(a);
    }
}