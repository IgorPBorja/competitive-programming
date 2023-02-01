/*
dp[k] = min_{1 <= i <= n | c[i] <= k}(dp[k-c[i]] + 1)
Do bottom up DP.
*/

#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, x;
    cin >> n >> x;
    int c[n];
    for (int i = 0; i < n; i++){
        cin >> c[i];
    }
    sort(c, c + n);

    long long dp[x + 1];
    for (int i = 0; i < x + 1; i++) dp[i] = (long long)(2e18);
    dp[0] = 0;

    // O(n*x)
    for (int i = 1; i < x + 1; i++){
        for (int j = 0; j < n; j++){
            if (c[j] > i) break;
            dp[i] = min(dp[i], dp[i - c[j]] + 1);
        }
    }
    if (dp[x] != (long long)(2e18)){
        cout << dp[x];
    } else {
        cout << -1;
    }
}