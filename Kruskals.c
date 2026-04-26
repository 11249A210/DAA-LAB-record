/*
 * ============================================================
 * Kruskal's Algorithm — Minimum Spanning Tree
 * ============================================================
 * Student ID : 11249A210
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: SCSVMV
 * ============================================================
 *
 * Aim:
 *   Connect all vertices of a graph with minimum total edge
 *   weight without forming any cycle.
 *
 * Approach:
 *   1. Collect all edges and arrange them by weight (ascending).
 *   2. Treat every vertex as a separate component (DSU init).
 *   3. Go through sorted edges one by one:
 *        - If the two endpoints belong to different components
 *          => include the edge, merge the components.
 *        - If both endpoints share the same component
 *          => skip (adding would create a cycle).
 *   4. Halt once (V-1) edges are selected.
 *
 * Disjoint Set Union (Union-Find):
 *   getRoot(x) : traces back to the root of x's component.
 *   combine(x,y): links two separate components into one.
 *
 * Complexity:
 *   Time  : O(E log E)  — sorting step is the bottleneck
 *   Space : O(V + E)
 * ============================================================
 */

#include <stdio.h>

#define MAX_V  20
#define MAX_E  100

/* Edge record */
typedef struct {
    int from, to, wt;
} Edge;

int  V, E;
Edge edgeList[MAX_E];
Edge spanTree[MAX_E];
int  component[MAX_V];
int  rnk[MAX_V];

/* ── Find root of vertex x with path compression ── */
int getRoot(int x)
{
    if (component[x] != x)
        component[x] = getRoot(component[x]);
    return component[x];
}

/* ── Merge two components (union by rank) ── */
void combine(int x, int y)
{
    int rx = getRoot(x);
    int ry = getRoot(y);

    if (rx == ry) return;

    if (rnk[rx] < rnk[ry])
        component[rx] = ry;
    else if (rnk[rx] > rnk[ry])
        component[ry] = rx;
    else {
        component[ry] = rx;
        rnk[rx]++;
    }
}

/* ── Bubble sort edges ascending by weight ── */
void arrangeEdges()
{
    for (int i = 0; i < E - 1; i++)
        for (int j = 0; j < E - i - 1; j++)
            if (edgeList[j].wt > edgeList[j + 1].wt) {
                Edge tmp      = edgeList[j];
                edgeList[j]   = edgeList[j + 1];
                edgeList[j+1] = tmp;
            }
}

/* ── Run Kruskal's and display results ── */
void kruskalMST()
{
    /* Initialise each vertex as its own component */
    for (int i = 0; i < V; i++) {
        component[i] = i;
        rnk[i]       = 0;
    }

    arrangeEdges();

    printf("\nEdge List (sorted by weight):\n");
    printf("%-8s %-8s %-8s\n", "From", "To", "Weight");
    printf("------------------------\n");
    for (int i = 0; i < E; i++)
        printf("%-8d %-8d %-8d\n",
               edgeList[i].from, edgeList[i].to, edgeList[i].wt);

    int count    = 0;
    int totalWt  = 0;

    printf("\nBuilding MST:\n");
    printf("%-8s %-8s %-8s %-14s\n", "From", "To", "Weight", "Decision");
    printf("--------------------------------------\n");

    for (int i = 0; i < E && count < V - 1; i++) {
        int u = edgeList[i].from;
        int v = edgeList[i].to;
        int w = edgeList[i].wt;

        if (getRoot(u) != getRoot(v)) {
            spanTree[count++] = edgeList[i];
            combine(u, v);
            totalWt += w;
            printf("%-8d %-8d %-8d INCLUDED\n", u, v, w);
        } else {
            printf("%-8d %-8d %-8d SKIPPED (cycle)\n", u, v, w);
        }
    }

    printf("\n================================================\n");
    printf("  Final Spanning Tree (Kruskal's)\n");
    printf("  %-8s %-8s %-8s\n", "From", "To", "Weight");
    printf("  ------------------------\n");
    for (int i = 0; i < count; i++)
        printf("  %-8d %-8d %-8d\n",
               spanTree[i].from, spanTree[i].to, spanTree[i].wt);
    printf("  ------------------------\n");
    printf("  Minimum Total Weight = %d\n", totalWt);
    printf("================================================\n");
}

int main()
{
    printf("================================================\n");
    printf("  Kruskal's Minimum Spanning Tree              \n");
    printf("  Student ID : 11249A210                       \n");
    printf("================================================\n\n");

    printf("Enter number of vertices : ");
    scanf("%d", &V);

    printf("Enter number of edges    : ");
    scanf("%d", &E);

    printf("Enter edges as: from  to  weight\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d",
              &edgeList[i].from,
              &edgeList[i].to,
              &edgeList[i].wt);
    }

    kruskalMST();

    return 0;
}

/*
 * -----------------------------------------------
 * Sample Run:
 *   Vertices: 5   Edges: 6
 *   0 1 2
 *   0 2 3
 *   1 2 5
 *   1 3 3
 *   2 4 4
 *   3 4 2
 *
 *   MST Edges:
 *   0 -- 1  wt: 2
 *   3 -- 4  wt: 2
 *   0 -- 2  wt: 3
 *   1 -- 3  wt: 3
 *   Total = 10
 * -----------------------------------------------
 */
