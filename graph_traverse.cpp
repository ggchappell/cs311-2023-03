// graph_traverse.cpp  UNFINISHED
// Glenn G. Chappell
// 2023-12-03
//
// For CS 311 Fall 2023
// Graph traversals: DFS & BFS

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <algorithm>
using std::lower_bound;
#include <stack>
using std::stack;
#include <queue>
using std::queue;
#include <cassert>
// For assert


// CONVENTIONS

// A GRAPH is represented by adjacency lists.
// We use N for the number of vertices in a graph. Vertices are numbered
// 0 .. N-1.
//
// Adjacency lists are stored in a vector<vector<int>> with size N. Item
// i in this vector is a list of the neighbors of vertex i, in ascending
// order.
//
// To create a graph represented by adjacency lists, call function
// emptyAdjLists to create a new edgeless graph. Then call function
// addEdge to add each edge to the graph.

// A traversal of a graph is printed as a list of vertex indices (each
// 0 .. n-1) separated by blanks.


// dfs
// Print Depth-First Search ordering of vertices of given graph. No
// terminating newline is printed.
//
// Pre:
//     adjlists holds the adjacency lists of an a graph (as above).
void dfs(const vector<vector<int>> & adjlists)
{
    cout << "<DFS NOT WRITTEN>" << endl;
}


// bfs
// Print Breadth-First Search ordering of vertices of given graph. No
// terminating newline is printed.
//
// Pre:
//     adjlists holds the adjacency lists of an a graph (as above).
void bfs(const vector<vector<int>> & adjlists)
{
    cout << "<BFS NOT WRITTEN>" << endl;
}


// printTraversals
// Given adjacency lists for graph, print DFS & BFS, each with
// terminating newline.
void printTraversals(const vector<vector<int>> & adjlists)
{
    cout << "DFS: ";
    dfs(adjlists);
    cout << "\n";

    cout << "BFS: ";
    bfs(adjlists);
    cout << "\n";
}


// emptyAdjLists
// Return adjacency lists (see above) for an edgeless graph with N
// vertices. Edges can then be added using addEdge.
//
// So, basically, this function is a constructor, except that we are not
// using a class here.
// Pre: None.
vector<vector<int>> emptyAdjLists(int N)
{
    return vector<vector<int>>(N);
}


// addEdge
// Adds edge a - b to graph described by adjlists (see above).
// Pre:
//     adjlists is valid adjacency lists (see above).
void addEdge(vector<vector<int>> & adjlists,
             int a, int b)
{
    assert (0 <= a);
    assert (size_t(a) < adjlists.size());
    assert (0 <= b);
    assert (size_t(b) < adjlists.size());

    // Insert b in adj list for vertex a; find spot with Binary Search.
    auto pos = lower_bound(adjlists[a].begin(), adjlists[a].end(), b);
    adjlists[a].insert(pos, b);

    // Insert a in adj list for vertex b; find spot with Binary Search.
    pos = lower_bound(adjlists[b].begin(), adjlists[b].end(), a);
    adjlists[b].insert(pos, a);
}


// makeAdjLists_tree
// Return adjacency lists for binary tree.
// Pre: None.
vector<vector<int>> makeAdjLists_tree()
{
    // Graph: Binary Tree
    // 7 vertices: 0 .. 6.
    // Adjacencies: 0 - 1, 0 - 2
    //              1 - 3, 1 - 4
    //              2 - 5, 2 - 6
    const int N = 7;
    auto adjlists = emptyAdjLists(N);

    addEdge(adjlists, 0, 1);
    addEdge(adjlists, 0, 2);
    addEdge(adjlists, 1, 3);
    addEdge(adjlists, 1, 4);
    addEdge(adjlists, 2, 5);
    addEdge(adjlists, 2, 6);

    return adjlists;
}


// makeAdjLists_cycle
// Return adjacency lists for cycle.
// Pre: None.
vector<vector<int>> makeAdjLists_cycle()
{
    // 8 vertices: 0 .. 7.
    // Adjacencies: 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 0
    const int N = 8;
    auto adjlists = emptyAdjLists(N);

    for (int i = 0; i < N; ++i)
    {
        addEdge(adjlists, i, (i+1)%N);
    }

    return adjlists;
}


// makeAdjLists_doublepath
// Return adjacency matrix for double path.
// Pre: None.
vector<vector<int>> makeAdjLists_doublepath()
{
    // Graph: two 5-paths
    // 10 vertices: 0 .. 9.
    // Adjacencies: 3 - 5 - 0 - 1 - 8
    //              7 - 2 - 4 - 9 - 6
    const int N = 10;
    auto adjlists = emptyAdjLists(N);

    addEdge(adjlists, 3, 5);
    addEdge(adjlists, 5, 0);
    addEdge(adjlists, 0, 1);
    addEdge(adjlists, 1, 8);
    addEdge(adjlists, 7, 2);
    addEdge(adjlists, 2, 4);
    addEdge(adjlists, 4, 9);
    addEdge(adjlists, 9, 6);

    return adjlists;
}


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Do DFS & BFS on various graphs, printing results.
int main()
{
    vector<vector<int>> adjlists;  // Holds adjacency lists

    // Print traversals for graphs

    // Tree
    cout << "Tree\n";
    adjlists = makeAdjLists_tree();
    printTraversals(adjlists);
    cout << "\n";

    // Cycle
    cout << "8-Cycle\n";
    adjlists = makeAdjLists_cycle();
    printTraversals(adjlists);
    cout << "\n";

    // Two Paths
    cout << "Two 5-Paths\n";
    adjlists = makeAdjLists_doublepath();
    printTraversals(adjlists);
    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

