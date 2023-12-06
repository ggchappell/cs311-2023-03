// prim.cpp  UNFINISHED
// Glenn G. Chappell
// 2023-12-05
//
// For CS 311 Fall 2023
// Prim's Algorithm

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <iomanip>
using std::setw;
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <utility>
using std::pair;


// CONVENTIONS

// A GRAPH is represented by adjacency lists.
// We use N for the number of vertices in a graph. Vertices are numbered
// 0 .. N-1.
//
// Adjacency lists are stored in a vector<vector<int>> with size N.
// Item i in this vector is a list of the neighbors of vertex i, in
// ascending order.

// A WEIGHTED GRAPH (weights on edges) is represented by a matrix of
// weights, possibly along with adjacency lists. The matrix is stored as
// a vector<vector<int>> with size N, in which all items have size N.
// Entry [i][j] holds the weight of the edge with endpoints i, j, if
// this edge exists. Otherwise it holds the special value NO_EDGE.
//
// To create a weighed graph represented as above, first set a constant
// N to the number of vertices. Call emptyWeightMatrix, passing N, to
// get a weight matrix for an N-vertex graph with all weights set to
// NO_EDGE. Make zero or more calls to setWeight to set the weights of
// various edges. Lastly, call makeAdjLists to get adjacency lists for
// the graph.


const int NO_EDGE = -1;       // In weight matrix, represents no edge

using Edge = pair<int, int>;  // Type for edge of graph
                              //  Integers are indices of endpoints


// prim
// Compute minimum spanning tree using Prim's Algorithm.
// Given weighted graph (represented as discussed above), order of
// graph, adjacency lists, and start vertex.
vector<Edge> prim(
    const vector<vector<int>> & adjlists,  // adjacency lists
    const vector<vector<int>> & wmatrix,   // weight matrix
    int start)                             // index of start vertex
{
    return vector<Edge>();  // Dummy
    // TODO: WRITE THIS!!!
}


// emptyWeightMatrix
// Return weight matrix (see above) for an edgeless graph with N
// vertices. Edge weights can then be added using setWeight.
//
// Basically, this function is a constructor, except that we are not
// using a class here.
vector<vector<int>> emptyWeightMatrix(int N)
{
    return vector<vector<int>>(N, vector<int>(N, NO_EDGE));
}


// setWeight
// Sets weight of a,b edge in weighted graph described by
//  wmatrix (see above).
void setWeight(vector<vector<int>> & wmatrix,
               int a, int b,
               int wt)
{
    wmatrix[a][b] = wt;
    wmatrix[b][a] = wt;
}


// printWeightMatrix
// Given a matrix stored in a vector, with the (i,j) entry stored in
// matrix[i*numcols+j], print the matrix, entries separated by blanks,
// rows ending with newline. Each entry is printed as its numerical
// value, or "-" if it is NO_EDGE. Column labels are printed above the
// matrix; row labels are printed to its left. All numbers are printed
// with a field width of 3, padded on the left with blanks.
void printWeightMatrix(const vector<vector<int>> & wmatrix)
{
    const int N = int(wmatrix.size());

    cout << "    | ";
    for (int col = 0; col < N; ++col)
    {
        cout << setw(3) << col << " ";
    }
    cout << "\n";

    cout << " ---+-";
    for (int col = 0; col < N; ++col)
    {
        cout << "----";
    }
    cout << "\n";

    for (int row = 0; row < N; ++row)
    {
        cout << setw(3) << row << " | ";
        for (int col = 0; col < N; ++col)
        {
            int value = wmatrix[row][col];
            if (value == NO_EDGE)
                cout << "  -";
            else
                cout << setw(3) << value;
            cout << " ";
        }
        cout << "\n";
    }
}


// makeAdjLists
// Given matrix representation of weighted graph (see above), return
// adjacency lists.
vector<vector<int>> makeAdjLists(const vector<vector<int>> & wmatrix)
{
    const int N = int(wmatrix.size());

    vector<vector<int>> adjlists(N, vector<int>());
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (wmatrix[i][j] != NO_EDGE)
                adjlists[i].push_back(j);
        }
    }
    return adjlists;
}


// printAdjacencyLists
// Given adjacency lists for a graph, print them, each lists on a
// separate line, preceded by the index of the vertex whose lists this
// is, entries separated by commas.
void printAdjacencyLists(const vector<vector<int>> & adjlists)
{
    const int N = int(adjlists.size());
    for (int i = 0; i < N; ++i)
    {
        cout << setw(3) << i << ": ";
        for (int j = 0; size_t(j) < adjlists[i].size(); ++j)
        {
            if (j != 0)
                cout << ", ";
            cout << adjlists[i][j];
        }
        cout << "\n";
    }
}


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Compute a minimum spanning tree using function prim. Print graph and
// result.
int main()
{
    const int N = 5;  // Number of vertices of graph

    // Set up weight matrix for graph;
    auto wmatrix = emptyWeightMatrix(N);
    setWeight(wmatrix, 0, 1, 7);
    setWeight(wmatrix, 0, 2, 6);
    setWeight(wmatrix, 0, 3, 2);
    setWeight(wmatrix, 0, 4, 8);
    setWeight(wmatrix, 1, 2, 3);
    setWeight(wmatrix, 1, 4, 4);
    setWeight(wmatrix, 2, 3, 5);
    setWeight(wmatrix, 2, 4, 1);
    setWeight(wmatrix, 3, 4, 9);

    // Print weights
    cout << "Weight matrix:" << "\n";
    printWeightMatrix(wmatrix);
    cout << "\n";

    // Compute & print adjacency lists
    auto adjlists = makeAdjLists(wmatrix);
    cout << "Adjacency lists:\n";
    printAdjacencyLists(adjlists);
    cout << "\n";

    // Pause before running algorithm
    cout << "Press ENTER to run Prim's Algorithm ";
    userPause();

    // Run Prim's Algorithm & print result
    const int start = 0;
    cout << "Running Prim's Algorithm "
         << "(start vertex: " << start << ") ... ";
    cout.flush();
    vector<Edge> tree = prim(adjlists, wmatrix, start);
    cout << "DONE\n" << endl;

    cout << "Edges in minimum spanning tree:\n";
    if (tree.size() == 0)
        cout << "[NONE]\n";
    for (int i = 0; size_t(i) < tree.size(); ++i)
    {
        cout << setw(3) << tree[i].first << ", " << tree[i].second
             << "\n";
    }
    cout << "\n";

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

