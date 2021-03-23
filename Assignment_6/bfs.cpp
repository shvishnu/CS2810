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
 *  Last Modified:    Tue 23-March-2021 22:14:56
 *
 *  Changes:        -
 *
 **************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <queue>

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
Graph<T>:: ~Graph() {                                      // Destructor for deallocating memory
    for(int i = 0; i < numVer; i++) {
        adjList[i].clear();
    }
    adjList.resize(0);
}

template <class T> 
void Graph<T>:: AddV() {                           
    numVer++;
    adjList.resize(numVer);             // Adding the new vertex as number numVer-1
}

template <class T>
void Graph<T>:: AddE(int a, int b, T w) {
    if(a >= numVer || b >= numVer) {        // Check if the vertex is valid
        cerr << "Invalid Vertex\n";
        return;
    }
    adjList[a].push_back({b, w});           // Add edge
    adjList[b].push_back({a, w});
}

template <class T>
void Graph<T>:: DelE(int a, int b) {
    if(a >= numVer || b >= numVer) {        // Chacking if the vertices are valid
        cerr << "Invalid Vertex\n";
        return;
    }
    bool ch1 = 0, ch2 = 0;
    for(auto p = adjList[a].begin(); p != adjList[a].end(); p++) {
        if((*p).first == b) {
            adjList[a].erase(p);        // Remove b from adjacency list of a
            ch1 = 1;
            break;
        }
    }
    for(auto p = adjList[b].begin(); p != adjList[b].end(); p++) {
        if((*p).first == a) {
            adjList[b].erase(p);        // Remove a from adjacency list of b
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

    // dist of source from source is zero
    dist[source] = 0;
    
    while(minDist.size()) {

        pair<T, int> del = minDist.top();        // top() returns the minimum element of the heap
        minDist.pop();
        int delVertex = del.second;                 // The deleted vertex
        T delDist = del.first;
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
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;       // To sort vertices in the order of distances
		auto p = q.front();
        x = p.second;
        cout << x << " ";           // Printing the BFS order
        q.pop();
		for(auto y: adjList[x])
        if(!vis[y.first]) {
            vis[y.first] = 1;
            pq.push({y.second, y.first});
        }

        while(pq.size()) {
            auto p = pq.top();
            q.push(p);
            pq.pop();
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
        if(s == "BFS") {
            G.BFS(a);
        }
        else {
            G.SSP(a);
        }
    }
}