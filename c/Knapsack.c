#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000
#define W 1000

int max(int a, int b) { return (a > b) ? a : b; }

int knapsack(int n, int w, int* weights, int* values) {
    int** dp = malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; ++i)
        dp[i] = calloc(w + 1, sizeof(int));

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= w; ++j) {
            if (weights[i - 1] <= j)
                dp[i][j] = max(dp[i - 1][j],
                               dp[i - 1][j - weights[i - 1]] + values[i - 1]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    int result = dp[n][w];
    for (int i = 0; i <= n; ++i) free(dp[i]);
    free(dp);
    return result;
}

int main() {
    int weights[N], values[N];
    srand(time(NULL));
    for (int i = 0; i < N; ++i) {
        weights[i] = rand() % 100 + 1;
        values[i] = rand() % 100 + 1;
    }

    int maxVal = knapsack(N, W, weights, values);
    printf("Max Value: %d\n", maxVal);
    return 0;
}
