/*
 * ============================================================
 * Bin Packing — First Fit Heuristic
 * ============================================================
 * Student ID : 11249A210
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: SCSVMV
 * ============================================================
 *
 * Aim:
 *   Pack n items of varying sizes into fixed-capacity bins
 *   using the First Fit strategy to minimise total bins used.
 *
 * First Fit Strategy:
 *   For each incoming item, iterate through open bins in order.
 *   Place the item into the VERY FIRST bin that has enough
 *   remaining space. If no existing bin can hold the item,
 *   open a brand new bin for it.
 *
 * Complexity:
 *   Time  : O(n^2)   — for each item, may scan all open bins
 *   Space : O(n)
 *   Ratio : <= 1.7 * OPT + 2  (approximation guarantee)
 * ============================================================
 */

#include <stdio.h>

/* ── First Fit Bin Packing ── */
void firstFitPack(int items[], int total, int binCap)
{
    int remaining[total];   /* remaining space in each bin */
    int openBins = 0;

    for (int i = 0; i < total; i++)
        remaining[i] = binCap;

    printf("\nFirst Fit Packing Process:\n");
    printf("------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        int placed = 0;

        /* Scan bins from the beginning — stop at first fit */
        for (int b = 0; b < openBins; b++) {
            if (remaining[b] >= items[i]) {
                remaining[b] -= items[i];
                printf("  Item %2d (size %3d) --> Bin %d  "
                       "[space left: %d]\n",
                       i + 1, items[i],
                       b + 1,
                       remaining[b]);
                placed = 1;
                break;   /* First Fit: stop immediately */
            }
        }

        if (!placed) {
            /* No existing bin fits — open a new one */
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
    printf("  Total Bins Used (First Fit) = %d\n", openBins);
}

int main()
{
    int n, cap;

    printf("================================================\n");
    printf("  Bin Packing — First Fit                      \n");
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

    firstFitPack(items, n, cap);

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
 *   Item 5 (size 2) --> Bin 2  [space left: 5]
 *   Total Bins = 3
 * -----------------------------------------------
 */
