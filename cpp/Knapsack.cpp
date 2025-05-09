#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 1000;
const int W = 1000;

int knapsack(int n, int w, const vector<int>& wt, const vector<int>& val) {
    vector<vector<int>> dp(n + 1, vector<int>(w + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= w; ++j)
            if (wt[i - 1] <= j)
                dp[i][j] = max(dp[i - 1][j],
                               dp[i - 1][j - wt[i - 1]] + val[i - 1]);
            else
                dp[i][j] = dp[i - 1][j];
    return dp[n][w];
}

int main() {
    vector<int> weights(N), values(N);
    srand(time(0));
    for (int i = 0; i < N; ++i) {
        weights[i] = rand() % 100 + 1;
        values[i] = rand() % 100 + 1;
    }

    int maxVal = knapsack(N, W, weights, values);
    cout << "Max Value: " << maxVal << endl;
    return 0;
}
