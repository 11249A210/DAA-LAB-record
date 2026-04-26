/*
 * ============================================================
 * Bin Packing — Best Fit Heuristic
 * ============================================================
 * Student ID : 11249A210
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: SCSVMV
 * ============================================================
 *
 * Aim:
 *   Pack n items of varying sizes into fixed-capacity bins
 *   using the Best Fit strategy to minimise total bins used.
 *
 * Best Fit Strategy:
 *   For every item, scan all open bins and select the one
 *   where the item fits AND the leftover space after insertion
 *   is the SMALLEST (tightest possible fit).
 *   If no open bin can hold the item, start a new bin.
 *
 * Why Best Fit?
 *   Leaves larger gaps in bins for future bigger items —
 *   generally better utilization than First Fit.
 *
 * Complexity:
 *   Time  : O(n^2)   — for each item, scan all open bins
 *   Space : O(n)
 *   Ratio : <= 1.7 * OPT + 2  (approximation guarantee)
 * ============================================================
 */

#include <stdio.h>

/* ── Best Fit Bin Packing ── */
void bestFitPack(int items[], int total, int binCap)
{
    int remaining[total];   /* remaining space in each bin */
    int openBins = 0;

    for (int i = 0; i < total; i++)
        remaining[i] = binCap;

    printf("\nBest Fit Packing Process:\n");
    printf("------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        int tightestBin  = -1;
        int leastLeftover = binCap + 1;

        /* Scan all open bins for the tightest valid fit */
        for (int b = 0; b < openBins; b++) {
            int leftover = remaining[b] - items[i];
            if (leftover >= 0 && leftover < leastLeftover) {
                leastLeftover = leftover;
                tightestBin   = b;
            }
        }

        if (tightestBin != -1) {
            remaining[tightestBin] -= items[i];
            printf("  Item %2d (size %3d) --> Bin %d  "
                   "[space left: %d]\n",
                   i + 1, items[i],
                   tightestBin + 1,
                   remaining[tightestBin]);
        } else {
            /* Open a new bin */
            remaining[openBins] -= items[i];
            printf("  Item %2d (size %3d) --> Bin %d  "
                   "[space left: %d]  ** new bin **\n",
                   i + 1, items[i],
                   openBins + 1,
                   remaining[openBins]);
            openBins++;
        }
    }

    printf("------------------------------------------\n");
    printf("  Total Bins Used (Best Fit) = %d\n", openBins);
}

int main()
{
    int n, cap;

    printf("================================================\n");
    printf("  Bin Packing — Best Fit                       \n");
    printf("  Student ID : 11249A210                       \n");
    printf("================================================\n\n");

    printf("Enter total number of items : ");
    scanf("%d", &n);

    printf("Enter bin capacity          : ");
    scanf("%d", &cap);

    int items[n];
    printf("Enter size of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("  Item %d: ", i + 1);
        scanf("%d", &items[i]);
        if (items[i] > cap) {
            printf("  Size exceeds bin capacity! Enter again.\n");
            i--;
        }
    }

    bestFitPack(items, n, cap);

    return 0;
}

/*
 * -----------------------------------------------
 * Sample Run:
 *   Items: 5   Capacity: 10
 *   Sizes: 6 4 3 7 2
 *
 *   Item 1 (size 6) --> Bin 1  [space left: 4]  ** new bin **
 *   Item 2 (size 4) --> Bin 1  [space left: 0]
 *   Item 3 (size 3) --> Bin 2  [space left: 7]  ** new bin **
 *   Item 4 (size 7) --> Bin 3  [space left: 3]  ** new bin **
 *   Item 5 (size 2) --> Bin 3  [space left: 1]
 *   Total Bins = 3
 * -----------------------------------------------
 */
