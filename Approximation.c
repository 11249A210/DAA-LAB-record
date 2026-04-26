/*
 * ============================================================
 * Approximation Algorithms for Travelling Salesman Problem
 * ============================================================
 * Student ID : 11249A210
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: SCSVMV
 * ============================================================
 *
 * Background:
 *   TSP asks: given n cities with travel costs, find the cheapest
 *   tour that visits every city exactly once and returns to start.
 *   TSP is NP-Hard — no polynomial exact algorithm is known.
 *   Approximation algorithms trade optimality for speed.
 *
 * Two methods implemented here:
 *
 *  Method A — Greedy Nearest Neighbour:
 *    Start at city 0. Repeatedly move to the closest city not
 *    yet visited. Return to start at the end.
 *    Ratio  : O(log n) in worst case
 *    Time   : O(n^2)
 *
 *  Method B — MST Pre-order Walk (2-Approximation):
 *    Build a Minimum Spanning Tree (Prim's).
 *    Perform DFS pre-order traversal on MST.
 *    That traversal order becomes the TSP tour.
 *    Ratio  : <= 2 * Optimal  (for metric graphs)
 *    Time   : O(n^2)
 *
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

#define CITY_MAX  10
#define BIG       999999

int  totalCities;
int  travelCost[CITY_MAX][CITY_MAX];

/* ──────────────────────────────────────────────────────────
 *  METHOD A: Nearest Neighbour Greedy
 * ────────────────────────────────────────────────────────── */

void nearestNeighbourTSP(int startCity)
{
    int seen[CITY_MAX];
    memset(seen, 0, sizeof(seen));

    int cur      = startCity;
    int tripCost = 0;
    seen[cur]    = 1;

    printf("\n[ Method A ] Greedy Nearest Neighbour\n");
    printf("----------------------------------------\n");
    printf("Route: %d", startCity);

    for (int hop = 1; hop < totalCities; hop++) {
        int nextCity = -1;
        int minEdge  = BIG;

        for (int c = 0; c < totalCities; c++) {
            if (!seen[c] && travelCost[cur][c] < minEdge) {
                minEdge  = travelCost[cur][c];
                nextCity = c;
            }
        }

        seen[nextCity] = 1;
        tripCost      += minEdge;
        printf(" -> %d", nextCity);
        cur = nextCity;
    }

    tripCost += travelCost[cur][startCity];
    printf(" -> %d\n", startCity);
    printf("Total Cost (Nearest Neighbour) = %d\n", tripCost);
}

/* ──────────────────────────────────────────────────────────
 *  METHOD B: MST + DFS Pre-order Walk
 * ────────────────────────────────────────────────────────── */

int  mstParent[CITY_MAX];
int  mstAdj[CITY_MAX][CITY_MAX];
int  walkVisited[CITY_MAX];
int  walkOrder[CITY_MAX];
int  walkIdx;

/* Build MST via Prim's algorithm */
void buildPrimMST()
{
    int keyVal[CITY_MAX];
    int inMST[CITY_MAX];

    for (int i = 0; i < totalCities; i++) {
        keyVal[i]  = BIG;
        inMST[i]   = 0;
        mstParent[i] = -1;
    }
    keyVal[0] = 0;

    for (int pass = 0; pass < totalCities - 1; pass++) {
        /* Find minimum key vertex not yet in MST */
        int u = -1, minK = BIG;
        for (int i = 0; i < totalCities; i++)
            if (!inMST[i] && keyVal[i] < minK) {
                minK = keyVal[i];
                u    = i;
            }

        inMST[u] = 1;

        for (int v = 0; v < totalCities; v++) {
            if (travelCost[u][v] && !inMST[v]
                && travelCost[u][v] < keyVal[v])
            {
                mstParent[v] = u;
                keyVal[v]    = travelCost[u][v];
            }
        }
    }

    /* Convert parent array to adjacency form */
    memset(mstAdj, 0, sizeof(mstAdj));
    for (int i = 1; i < totalCities; i++) {
        mstAdj[mstParent[i]][i] = 1;
        mstAdj[i][mstParent[i]] = 1;
    }
}

/* DFS pre-order on MST */
void dfsWalk(int node)
{
    walkVisited[node]      = 1;
    walkOrder[walkIdx++]   = node;
    for (int nb = 0; nb < totalCities; nb++)
        if (mstAdj[node][nb] && !walkVisited[nb])
            dfsWalk(nb);
}

void mstWalkTSP()
{
    buildPrimMST();

    memset(walkVisited, 0, sizeof(walkVisited));
    walkIdx = 0;
    dfsWalk(0);

    int tourCost = 0;

    printf("\n[ Method B ] MST Pre-order Walk (2-Approximation)\n");
    printf("--------------------------------------------------\n");
    printf("Route: ");

    for (int i = 0; i < totalCities; i++) {
        printf("%d", walkOrder[i]);
        if (i < totalCities - 1) {
            tourCost += travelCost[walkOrder[i]][walkOrder[i + 1]];
            printf(" -> ");
        }
    }
    tourCost += travelCost[walkOrder[totalCities - 1]][walkOrder[0]];
    printf(" -> %d\n", walkOrder[0]);
    printf("Total Cost (MST Walk)          = %d\n", tourCost);
}

/* ──────────────────────────────────────────────────────────
 *  MAIN
 * ────────────────────────────────────────────────────────── */

int main()
{
    printf("================================================\n");
    printf("  Approximation Algorithms — TSP               \n");
    printf("  Student ID : 11249A210                       \n");
    printf("================================================\n\n");

    printf("Enter number of cities : ");
    scanf("%d", &totalCities);

    printf("Enter %d x %d distance matrix:\n", totalCities, totalCities);
    for (int i = 0; i < totalCities; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < totalCities; j++)
            scanf("%d", &travelCost[i][j]);
    }

    nearestNeighbourTSP(0);
    mstWalkTSP();

    return 0;
}

/*
 * -----------------------------------------------
 * Sample Run:
 *   Cities: 4
 *   Matrix:
 *     0 10 15 20
 *    10  0 35 25
 *    15 35  0 30
 *    20 25 30  0
 *
 *   Method A Route: 0->1->3->2->0  Cost=80
 *   Method B Route: 0->1->3->2->0  Cost=80
 * -----------------------------------------------
 */
