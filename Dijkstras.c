/*
 * ============================================================
 * Shortest Path Finding — Dijkstra's Method
 * ============================================================
 * Student ID : 11249A210
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: SCSVMV
 * ============================================================
 *
 * Aim:
 *   For a given weighted graph, compute the minimum distance
 *   from a chosen source node to every other node.
 *
 * Steps:
 *   1. Assign distance 0 to source, infinity to rest.
 *   2. Select the nearest unprocessed node (u).
 *   3. Lock u as processed.
 *   4. Relax all neighbours of u:
 *        if cost[u] + edge(u,v) < cost[v]  =>  update cost[v]
 *   5. Continue until every node is processed.
 *
 * Complexity:
 *   Time  : O(V^2) using adjacency matrix
 *   Space : O(V)
 *
 * Note: Only works with non-negative edge weights.
 * ============================================================
 */

#include <stdio.h>

#define MAX_NODES  10
#define LARGE_VAL  999999

int numNodes;

/* Returns the unprocessed node with the smallest tentative distance */
int pickMinNode(int cost[], int done[])
{
    int smallest = LARGE_VAL;
    int chosen   = 0;

    for (int i = 0; i < numNodes; i++) {
        if (!done[i] && cost[i] < smallest) {
            smallest = cost[i];
            chosen   = i;
        }
    }
    return chosen;
}

/* Recursively prints path from source to node v */
void showPath(int prev[], int v)
{
    if (prev[v] == -1) {
        printf("%d", v);
        return;
    }
    showPath(prev, prev[v]);
    printf(" => %d", v);
}

/* Core Dijkstra routine */
void findShortestPaths(int graph[MAX_NODES][MAX_NODES], int src)
{
    int cost[MAX_NODES];
    int done[MAX_NODES];
    int prev[MAX_NODES];

    for (int i = 0; i < numNodes; i++) {
        cost[i] = LARGE_VAL;
        done[i] = 0;
        prev[i] = -1;
    }
    cost[src] = 0;

    for (int step = 0; step < numNodes - 1; step++) {
        int u = pickMinNode(cost, done);
        done[u] = 1;

        for (int v = 0; v < numNodes; v++) {
            if (!done[v]
                && graph[u][v] != 0
                && cost[u] != LARGE_VAL
                && cost[u] + graph[u][v] < cost[v])
            {
                cost[v] = cost[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    printf("\nShortest Paths from Node %d:\n", src);
    printf("------------------------------------------------\n");
    printf("%-8s %-12s %-20s\n", "Node", "Min Cost", "Route");
    printf("------------------------------------------------\n");

    for (int i = 0; i < numNodes; i++) {
        printf("%-8d ", i);
        if (cost[i] == LARGE_VAL)
            printf("%-12s ", "NOT REACHABLE");
        else
            printf("%-12d ", cost[i]);
        showPath(prev, i);
        printf("\n");
    }
}

int main()
{
    int graph[MAX_NODES][MAX_NODES];

    printf("================================================\n");
    printf("  Dijkstra's Shortest Path                     \n");
    printf("  Student ID : 11249A210                       \n");
    printf("================================================\n\n");

    printf("Number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the %d x %d cost matrix\n", numNodes, numNodes);
    printf("(use 0 where no direct connection exists)\n");

    for (int i = 0; i < numNodes; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < numNodes; j++)
            scanf("%d", &graph[i][j]);
    }

    int src;
    printf("Source node (0 to %d): ", numNodes - 1);
    scanf("%d", &src);

    findShortestPaths(graph, src);

    return 0;
}

/*
 * -----------------------------------------------
 * Sample Run:
 *   Nodes: 5
 *   Matrix:
 *     0 10  0  0 5
 *    10  0  1  0 2
 *     0  1  0  4 0
 *     0  0  4  0 0
 *     5  2  0  0 0
 *   Source: 0
 *
 *   Node 0  Cost: 0   Route: 0
 *   Node 1  Cost: 7   Route: 0 => 4 => 1
 *   Node 2  Cost: 8   Route: 0 => 4 => 1 => 2
 *   Node 3  Cost: 12  Route: 0 => 4 => 1 => 2 => 3
 *   Node 4  Cost: 5   Route: 0 => 4
 * -----------------------------------------------
 */
