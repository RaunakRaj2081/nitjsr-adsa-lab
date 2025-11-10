// Write a function to implement the travelling sales person problem. Prepare the table of running time for 
// graphs containing 10, 20, 40, 60 and 100 nodes and draw graph problem-size versus execution time. 
#include <stdio.h>
#include <limits.h>
#include <math.h>

#define N 15  // keep small for demo

int n, dist[N][N];
int dp[1<<N][N];  // DP table

int tsp(int mask, int pos) {
    if(mask == (1<<n)-1) return dist[pos][0]; // return to start
    if(dp[mask][pos] != -1) return dp[mask][pos];

    int ans = INT_MAX;
    for(int city=0; city<n; city++) {
        if(!(mask & (1<<city))) {
            int newAns = dist[pos][city] + tsp(mask | (1<<city), city);
            if(newAns < ans) ans = newAns;
        }
    }
    return dp[mask][pos] = ans;
}

int main() {
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&dist[i][j]);

    for(int i=0;i<(1<<n);i++)
        for(int j=0;j<n;j++)
            dp[i][j] = -1;

    printf("Minimum Cost: %d\n", tsp(1,0));
    return 0;
}
