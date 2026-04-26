/*
 * ============================================================
 * QuickSort — Divide and Conquer Sorting
 * ============================================================
 * Student ID : 11249A210
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: SCSVMV
 * ============================================================
 *
 * Aim:
 *   Sort a list of integers in ascending order using the
 *   QuickSort algorithm.
 *
 * Strategy (Divide and Conquer):
 *   1. Select a PIVOT — here the FIRST element is chosen.
 *   2. PARTITION the sub-array:
 *        All elements < pivot go to its left.
 *        All elements > pivot go to its right.
 *        Pivot settles at its correct sorted position.
 *   3. Recursively sort the left and right halves.
 *   4. Base case: sub-array length <= 1 → already sorted.
 *
 * Partition Scheme Used: Hoare-style with first element as pivot.
 *   - left pointer moves right while arr[left] <= pivot.
 *   - right pointer moves left while arr[right] > pivot.
 *   - Swap when left < right; stop when pointers cross.
 *   - Place pivot at the crossing point.
 *
 * Complexity:
 *   Best / Average : O(n log n)
 *   Worst case     : O(n^2)  — sorted input with first-element pivot
 *   Space          : O(log n) recursive stack
 * ============================================================
 */

#include <stdio.h>

/* ── Exchange two array elements ── */
void exchange(int *x, int *y)
{
    int hold = *x;
    *x = *y;
    *y = hold;
}

/* ── Display array contents ── */
void display(int arr[], int size)
{
    printf("{ ");
    for (int i = 0; i < size; i++)
        printf("%d%s", arr[i], i < size - 1 ? ", " : " ");
    printf("}\n");
}

/*
 * split - Partitions arr[lo..hi] around first element as pivot.
 *         Returns the final position of the pivot.
 */
int split(int arr[], int lo, int hi)
{
    int pivot = arr[lo];   /* first element as pivot */
    int left  = lo + 1;
    int right = hi;

    printf("  Pivot = %d  |  Segment: ", pivot);
    for (int k = lo; k <= hi; k++)
        printf("%d ", arr[k]);
    printf("\n");

    while (left <= right) {
        /* Advance left while elements are <= pivot */
        while (left <= hi && arr[left] <= pivot)
            left++;
        /* Retreat right while elements are > pivot */
        while (right > lo && arr[right] > pivot)
            right--;

        if (left < right)
            exchange(&arr[left], &arr[right]);
    }

    /* Put pivot in its correct place */
    exchange(&arr[lo], &arr[right]);

    printf("  Result:       ");
    for (int k = lo; k <= hi; k++)
        printf("%d ", arr[k]);
    printf("  (pivot %d settled at index %d)\n\n", pivot, right);

    return right;
}

/*
 * qsort_rec - Recursively sorts arr[lo..hi].
 */
void qsort_rec(int arr[], int lo, int hi)
{
    if (lo < hi) {
        int pivotPos = split(arr, lo, hi);
        qsort_rec(arr, lo,          pivotPos - 1);
        qsort_rec(arr, pivotPos + 1, hi);
    }
}

/* ── Main ── */
int main()
{
    int n;

    printf("================================================\n");
    printf("  QuickSort — Divide and Conquer               \n");
    printf("  Student ID : 11249A210                       \n");
    printf("================================================\n\n");

    printf("How many elements to sort? ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nInput  : ");
    display(arr, n);

    printf("\n--- Sorting Steps ---\n\n");
    qsort_rec(arr, 0, n - 1);

    printf("Sorted : ");
    display(arr, n);

    printf("\n================================================\n");
    printf("  Best/Avg Time  : O(n log n)                  \n");
    printf("  Worst Time     : O(n^2)                      \n");
    printf("  Stack Space    : O(log n)                    \n");
    printf("================================================\n");

    return 0;
}

/*
 * -----------------------------------------------
 * Sample Run:
 *   Input: 5 elements — 40 20 60 10 50
 *
 *   Pivot=40 | Segment: 40 20 60 10 50
 *   Result: 10 20 40 60 50  (pivot 40 at index 2)
 *
 *   Pivot=10 | Segment: 10 20
 *   Result: 10 20           (pivot 10 at index 0)
 *
 *   Pivot=60 | Segment: 60 50
 *   Result: 50 60           (pivot 60 at index 1)
 *
 *   Sorted: { 10, 20, 40, 50, 60 }
 * -----------------------------------------------
 */
