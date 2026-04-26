#include <stdio.h>
#include <stdlib.h>
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

    // printIndent(depth);
    // printf("-> [%s] K(W=%d, n=%d) returned: %d\n", choice, W, n, result);

    return result;
}
// Driver Code
int main()
{
    const char *filename = "datasets/1x.txt"; 
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1; 
    }

    int n, W;
    
    // read the header lines: "n 1000" and "W 500"
    fscanf(file, "n %d\n", &n);
    fscanf(file, "W %d\n", &W);

    int *values = (int *)malloc(n * sizeof(int));
    int *weights = (int *)malloc(n * sizeof(int));

    if (values == NULL || weights == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    // read all the values
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &values[i]);
    }

    // read all the weights
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &weights[i]);
    }

    fclose(file);

    clock_t t1, t2;
    double  t;

    // ---- print size and capacity
    printf("Size (n)  : %d\n", n);
    printf("Capacity (W)  : %d\n", W);

    // // ---- print value and weight arrays
    // print_array("Values ", values, n);
    // print_array("Weights", weights,  n);
    // printf("\n");

    /* START CLOCK */
    t1 = clock();

    // printf("Recursion Tree Trace:\n\n");

    // Output the maximum profit for the knapSack
    // Pass 0 as the starting depth
    int max_val = knapsackRecursive(W, weights, values, n, 0, "ROOT");
    
    // printf("\nMaximum value that can be put in knapsack: %d\n", max_val);

    /* STOP CLOCK */
    t2 = clock();
    t  = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;

    printf("Time elapsed  : %f s\n", t);

    return 0;
}