#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

int main(){
    i64 n;
    cin >> n;
    i64 dp[n][n]; 
    // dp[i][j] = max jump when starting on i with speed of j
    // dp[i][j] = 1 + dp[i + k][k] with k <= min(n - 1 - i, j) and l <= j
}