#include <stdio.h>
#include <time.h>   // clock_t, clock(), CLOCKS_PER_SEC

// Function to find maximum between two numbers
int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

// ---- print array
void print_array(const char *label, int *arr, int n) {
    printf("%s: [ ", label);        // print the label first
    for (int i = 0; i < n; i++)     // loop through every element
        printf("%d ", arr[i]);      // print each element with space
    printf("]\n");                  
} 

// Helper function to print indentation for the recursion tree
void printIndent(int depth)
{
    for (int i = 0; i < depth; i++) {
        printf("  | ");
    }
}

// Returns the maximum value that can be put in a knapsack
// of capacity W
int knapsackRecursive(int W, int wt[], int val[], int n, int depth, const char* choice)
{

    int result;

    // Base Case
    // if no items are left (n=0) or the bag is full (W=0)
    if (n == 0 || W == 0) {
        result = 0;
    }

    // if the current item is heavier than the room left in the bag, we ignore it and check the remaining n-1 items
    else if (wt[n - 1] > W) {
        result = knapsackRecursive(W, wt, val, n - 1, depth + 1, "SKIP");
    }

    // the item fits, so we find the maximum value by checking two possibilities:
    // 1. Including item (val[n-1] + recurse with W - weight)
    // 2. Excluding item (recurse with same W)
    else {
        result = max(val[n - 1] 
                       + knapsackRecursive(W - wt[n - 1], wt, val, n - 1, depth + 1, "INCLUDE"),
                   knapsackRecursive(W, wt, val, n - 1, depth + 1, "EXCLUDE"));
    }

    printIndent(depth);
    printf("-> [%s] K(W=%d, n=%d) returned: %d\n", choice, W, n, result);

    return result;
}
// Driver Code
int main()
{
    int values[] = {3, 4, 5, 6};    
    int weight[] = {2, 3, 4, 5};    
    int W        = 8;                                   // capacity
    int n        = sizeof(values) / sizeof(values[0]);  // n size

    clock_t t1, t2;
    double  t;

    // ---- print capacity
    printf("Capacity (W)  : %d\n\n", W);

    // ---- print value and weight arrays
    print_array("Values ", values, n);
    print_array("Weights", weight,  n);
    printf("\n");

    /* START CLOCK */
    t1 = clock();

    printf("Recursion Tree Trace:\n\n");

    // Output the maximum profit for the knapSack
    // Pass 0 as the starting depth
    int max_val = knapsackRecursive(W, weight, values, n, 0, "ROOT");
    
    printf("\nMaximum value that can be put in knapsack: %d\n", max_val);

    /* STOP CLOCK */
    t2 = clock();
    t  = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;

    printf("Time elapsed  : %f s\n", t);

    return 0;
}