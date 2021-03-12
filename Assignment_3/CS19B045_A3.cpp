/**************************************************************************
 *  
 *  File:    CS19B045_A3.cpp
 *
 *  Purpose:    Stack implementation and DFS in graph
 *
 *  Author:    Vishnu
 *
 *  Created:    Mon 22-February-2021 18:05:34
 *
 *  Last Modified:    Tue 23-February-2021 14:25:12
 *
 *  Changes:    - 
 *
 **************************************************************************/
#include <iostream>
#include <string>
#include <utility>

using namespace std;

typedef struct CellType* Position;          //Position is the pointer of object type CellType

struct CellType {               // Structure to store the value and next linked element
    int value;                          // Integer value
    Position next;
};

/* Definition of Class Stack */
class Stack {

    public:
        void push(int);         //member functions
        int pop();
        void makeNull();
        int isEmpty();
        int top();

    private:
        Position stackTop;      //Stacktop
};

void Stack::makeNull() {
    stackTop = NULL;                // Initialized to NULL
}

void Stack::push(int val) {             // push val into the stack
    Position temp;

    temp = new CellType;
    temp->value = val;
    temp->next = stackTop;

    stackTop = temp;
}

int Stack::pop() {                  // pop top

    if(isEmpty()) 
        return -1;                      // return -1 if no element to pop

    Position temp = stackTop;
    int del = temp->value;              // deleted value
    stackTop = stackTop->next;          // move topo to next position
    
    temp->next = NULL;
    free(temp);                     // free deleted memory

    return del;     // return deleted value
}

int Stack::isEmpty() {
    if(stackTop == NULL) return 1;              // return 1 if stack is empty
    return 0;
}

int Stack::top() {

    if(isEmpty()) 
        return -1;

    return (stackTop->value);           // return stack top
}

/*Definition of class Graph*/
class Graph {

    int **adjMat;                    // Adjacency matrix
    int vertices;                   // Number of vertices

    public :
        // Function declarations
        Graph(int);
        void operator+=(const pair<int, int>&);
        void operator-= (const pair<int, int>&);
        int components();
        bool reach(int, int);
        bool detectCycle();
        bool cycle(int, bool visited[], int);
};

Graph::Graph(int n) {                                 // Constructor to allocate memory

    vertices = n;
    adjMat = new int* [vertices];

    for(int i = 0; i < vertices; i++) { 
        adjMat[i] = new int [vertices];            // Allocate each array

        for(int j = 0; j < vertices; j++) {
            adjMat[i][j] = 0;                      // Initialize to zero
        }
    }
}

void Graph::operator+= (const pair<int, int>& edge) {               // Function to add undirected edge uv
    int u = edge.first, v = edge.second;                                     
    adjMat[u][v] = 1;                   // add edge u->v
    adjMat[v][u] = 1;                   // add edge v->u
}

void Graph::operator-= (const pair<int, int>& edge) {               // Function to remove undirected edge uv             
    int u = edge.first, v = edge.second;                                     
    adjMat[u][v] = 0;                   // remove edge u->v
    adjMat[v][u] = 0;                   // remove edge v->u
}


/**    DESCRIPTION OF THE FUNCTION
 * components - Finds the number of connected components of graph
 *        
 * parameter    nil
 *
 * return    int (number of components)
 * 
 */
int Graph::components() {

    bool visited[vertices] = {};
    Stack stack;
    stack.makeNull();
    int numComponents = 0;

    for(int i = 0; i < vertices; i++) {

        if(visited[i]) continue;                    // Skip if i has been visited

        stack.push(i);
        while(!stack.isEmpty()) {
            int v = stack.top();
            stack.pop();
            visited[v] = 1;                         // Mark v as visited
            for(int u = 0; u < vertices; u++) {
                if(adjMat[u][v] && !visited[u]) {           
                    stack.push(u);                  // Push to stack when u is adjacent to v and has not yet been visited
                }
            }
        }
        numComponents++;                // Increment the number of components
    }
    return numComponents;
}

/**    DESCRIPTION OF THE FUNCTION
 * reach - Finds if there is a path from u to v
 *        
 * parameter    int, int 
 *
 * return    bool (1 if path exists, else 0) 
 * 
 */
bool Graph::reach(int u, int v) {           

    bool visited[vertices] = {};

    Stack stack;
    stack.makeNull();
    stack.push(u);                  // push starting vertex

    while(!stack.isEmpty()) {
        int y = stack.top();
        stack.pop();
        visited[y] = 1;                     // Mark y as visited

        if(y == v) break;                       // If v is reached from u, break

        for(int x = 0; x < vertices; x++) {
            if(adjMat[x][y] && !visited[x]) {
                stack.push(x);                          // push x if it is adjacent to y and not yet visited
            }
        }
    }

    return visited[v];
}

/**    DESCRIPTION OF THE FUNCTION
 * detectCycle - Finds if there is a cycle in the graph
 *        
 * parameter    nil
 *
 * return    bool (1 if cycle exists, else 0) 
 * 
 */
bool Graph::detectCycle() {
    bool visited[vertices] = {};

    for(int i = 0; i < vertices; i++) {         // Required if there are more than 1 connected component

        if(!visited[i]) {
            if(cycle(i, visited, -1)) {             // check for back edge (third parameter is parent of 0 which is given as -1)
                return 1;
            }
        }
    }
    return 0;
}

/**    DESCRIPTION OF THE FUNCTION
 * cycle - helper function to find if there is a cycle in the graph
 *        
 * parameter    int, bool[], int
 *
 * return    bool (1 if cycle exists, else 0) 
 * 
 * checks if there is a back edge which is the condition for cycle during dfs
 * 
 */
bool Graph::cycle(int u, bool visited[], int p) {

    if(visited[u])                  // Checks for a back edge
        return 1;                        

    visited[u] = 1;                 // Mark u as visited

    for(int v = 0; v < vertices; v++) {
        if(adjMat[u][v] == 0)               // continue if v and u are not adjacent
            continue;
        if(v != p && cycle(v, visited, u)) return 1;               // return true if there is a backedge from v
    }

    return 0;
}

int main() {
    int Q, val;
    string s;
    Stack stack;
    stack.makeNull();           // Allocate memory for Stack stack

    cin >> Q;                       // Number of queries
    while(Q--) {
        cin >> s;
        if(s == "push") {
            cin >> val;
            stack.push(val);
        }

        else if(s == "pop") {
            cout << stack.pop() << endl;
        }

        else if(s == "top") {
            cout << stack.top() << endl;
        }

        else if(s == "empty") {
            cout << stack.isEmpty() << endl;
        }
    }

    int n, m, u, v;

    cin >> n;
    cin >> m;
    Graph G(n);                 // Initialize graph G

    while(m--) {
        cin >> s;
        if(s == "add") {
            cin >> u >> v;
            G+=make_pair(u, v);         // add edge
        }

        else if(s == "del") {
            cin >> u >> v;
            G-=make_pair(u, v);             // remove edge
        }

        else if(s == "components") {
            cout << G.components() << endl;
        }

        else if(s == "reach") {
            cin >> u >> v;
            cout << G.reach(u, v) <<  endl;
        }

        else if(s == "cycle") {
            cout << G.detectCycle() <<  endl;
        }
    }
}