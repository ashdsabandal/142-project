#include <stdio.h>
#include <time.h>   // clock_t, clock(), CLOCKS_PER_SEC

// returns maximum of two integers
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

// tabulation method
void knapSackTabulation(int W, int wt[], int val[], int n) {

    // dp table 2d array
    int dp[n + 1][W + 1];

    // initialize dp table
    for (int i = 0; i <= n; i++) {          // loop over each item (0 = no item)
        for (int w = 0; w <= W; w++) {      // loop over each capacity 0 to W
            if (i == 0 || w == 0)
                dp[i][w] = 0;               // base case: no items OR no capacity -> value is always 0
            
            else if (wt[i - 1] <= w)        // current item does not fit at capacity
                dp[i][w] = max(             // formula  
                    val[i - 1] + dp[i - 1][w - wt[i - 1]],
                    dp[i - 1][w]);
            
            else
                dp[i][w] = dp[i - 1][w];    // current item does not fit at capacity w
        }
    }

    // ---- print capacity
    printf("Capacity (W)  : %d\n\n", W);

    // ---- print value and weight arrays
    print_array("Values ", val, n);
    print_array("Weights", wt,  n);
    printf("\n");

    // ---- print 2d dp table 

    // ---- header row showing each capacity value
    printf("        ");
    for (int w = 0; w <= W; w++)
        printf("W=%-3d ", w);
    printf("\n");

    // ---- divider
    printf("        ");
    for (int w = 0; w <= W; w++)
        printf("------");
    printf("\n");

    // ---- dp table rows 
    for (int i = 0; i <= n; i++) {
        printf("i=%-2d  | ", i);        // item index
        for (int w = 0; w <= W; w++)
            printf("%-6d", dp[i][w]);   // each cell value
        printf("\n");
    }
    printf("\n");

    // ---- backtrack to find included/excluded items 
    // start at dp[n][W] (bottom-right corner)
    // at each row i, if dp[i][w] != dp[i-1][w], the item i was INCLUDED -> mark it,
    // reduce capacity by its weight, move up
    // otherwise the item was SKIPPED -> just move up

    int included[n];

    for (int i = 0; i < n; i++) 
        included[i] = 0;            // initialize array [0 0 0 0 ... 0]

    int sz = W;                     
    for (int i = n; i > 0; i--) {
        if (dp[i][sz] != dp[i - 1][sz]) {
            included[i - 1] = 1;
            sz -= wt[i - 1];
        }
        // if dp[i][sz] == dp[i-1][sz], skip - do nothing
    }

    // ----- print x_n included/excluded 
    printf("Item Selection (x_n):\n");
    printf("  %-8s %-8s %-8s %-15s\n", "Item",   "Weight", "Value", "x_n");
    printf("  %-8s %-8s %-8s %-15s\n", "----",   "------", "-----", "---");
    for (int i = 0; i < n; i++) {
        if (included[i]) {
        printf("  x_%-5d %-8d %-8d %s\n",
                i + 1, wt[i], val[i],
                "1 (included)"
            );
        }
        else {
            printf("  x_%-5d %-8d %-8d %s\n",
                i + 1, wt[i], val[i],
                "0 (excluded)"
            );
        }
    }

    printf("\n");

    // source code
    printf("Maximum value that can be put in knapsack: %d\n", dp[n][W]);
}

int main() {
    int values[] = {3, 4, 5, 6};    
    int weight[] = {2, 3, 4, 5};    
    int W        = 8;                                   // capacity
    int n        = sizeof(values) / sizeof(values[0]);  // n size

    clock_t t1, t2;
    double  t;

    /* START CLOCK */
    t1 = clock();

    knapSackTabulation(W, weight, values, n);

    /* STOP CLOCK */
    t2 = clock();
    t  = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;

    printf("Time elapsed  : %f s\n", t);

    return 0;
}

// test cases:
// v[ 3, 4, 5, 6 ]  w[ 2, 3, 4, 5 ]  W = 8
// v[ 1, 2, 5, 6 ]  w[ 2, 3, 4, 5 ]  W = 8
// v[ 2, 2, 4, 5, 3 ]  w[ 3, 1, 3, 4, 2 ]  W = 7