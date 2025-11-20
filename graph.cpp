/*************************************************************************
 * AUTHORS	: Eric, Amy, Aspen
 * CLASS	: CS 1D
 * DUE DATE	: 11/19/25
 * ASSIGN	: 11
 *************************************************************************/

#include "graph.h"

Graph::Graph() {}

void Graph::dijkstra(int start)
{
    int n = adjacencyMatrix.size();

    /**********************************************
     * 1. INITIALIZE DISTANCES
     **********************************************/
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);

    dist[start] = 0;   // start node distance = 0

    /**********************************************
     * 2. MAIN LOOP
     *    Repeat until all vertices are visited
     **********************************************/
    for (int count = 0; count < n - 1; count++)
    {
        /******************************************
         * VISIT SMALLEST EDGE (Find min dist node)
         ******************************************/
        int u = -1;          // index of vertex to visit
        int MIN = INT_MAX;   // current minimum distance

        // Find the unvisited vertex with smallest dist[]
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && dist[i] < MIN)
            {
                MIN = dist[i];
                u = i;
            }
        }

        // If no reachable unvisited node remains, break
        if (u == -1)
            break;

        visited[u] = true;   // Mark this vertex as visited


        /******************************************
         * RELAX SURROUNDING NODES
         * - Only relax UNVISITED neighbors
         * - Only relax edges that exist (weight != -1)
         ******************************************/
        for (int v = 0; v < n; v++)
        {
            int weight = adjacencyMatrix[u][v];

            if (weight != -1)                        // edge exists
            {
                if (!visited[v] &&                   // cannot relax visited node
                    dist[u] != INT_MAX &&            // must be reachable
                    dist[u] + weight < dist[v])      // relaxation condition
                {
                    dist[v] = dist[u] + weight;      // update shortest distance
                    parent[v] = u;                   // store path (current shortest)
                }
            }
        }
    }

    cout << left;

    //Print distances
    for (int i = 0; i < n; i++)
    {
        cout << "Distance from " << indexToCity[0]
             << " to " <<  indexToCity[i] << " = " << dist[i] << endl;
    }
    cout << right;

    //Print path
    cout << "Final path: ";
    for (int i = 0; i < n; i++)
    {
        cout << indexToCity[i];
        if (i == n - 1)
        {
        	cout << " ";
        }
        else
        {
        	cout << ", ";
        }
    }
    cout << right;

};

/***************************************************************************
 * mst
 * -------------------------------------------------------------------------
 * using Prim-Jarnik's code
 *      start   - starting vertex
 **************************************************************************/
void Graph::mst(int start) {
    /***********************************************************************
     * INITIALIZE
     **********************************************************************/
    const int SIZE = adjacencyMatrix.size();        // number of cities

    vector<bool> visited;                           // vertex visited
    vector<int> orderVisit;                         // list of cities visited
    priority_queue<pair<int, int>> unlocked;        // list of cities we can look at (weight, city)

    /***********************************************************************
     * Initalizing unlocked list
     **********************************************************************/
    unlocked.push({-1, start});
    
    while (!unlocked.empty()) {

        /*******************************************************************
         * 1. Get the smallest distance city
         ******************************************************************/
        int city = unlocked.top().second;       // city we are looking at

        // Remove city from list
        unlocked.pop();

        /*******************************************************************
         * 2. Check if smallest distance city is NOT visited
         ******************************************************************/
        if (visited[city] == false) {
         
            // Mark as visited
            visited[city] = true;
            // Add to list of visited cities
            orderVisit.push_back(city);

        } // END if (visited[city] == false)

        /*******************************************************************
         * Add adjacent cities to list of unlocked cities
         ******************************************************************/
        for (int i = 0; i < adjacencyMatrix[city].size(); i++) {

            /***************************************************************
             * Check if city NOT visited
             **************************************************************/
            if (visited[i] == false) {
                // add to list of cities we can visit
                unlocked.push({adjacencyMatrix[city][i], i});
            } // END if (visited[i] == false)

        } // END for (int i = 0; i < SIZE; i++)

    } // END while (!unlocked.empty())

} // END mst