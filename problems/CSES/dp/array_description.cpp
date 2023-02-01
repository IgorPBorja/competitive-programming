/*
--> optimize for cache hit
--> max space: O(mn)
let dp[i][j] be the number of subarrays B[0...i] that end in j and match the subarray A[0...i]
for 0 <= i <= n - 1, 0 <= j <= m<= 100

then 
if a[i+1] != 0 && j != a[i+1]
    dp[i+1][j] = 0
else
    dp[i+1][j] = (j != 1)dp[i][j-1] + dp[i][j] + (j != m)dp[i][j+1]
*/

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main(){
    int n, m;
    cin >> n >> m;
    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    int dp[n][m + 1];
    // initialize all to 0
    for (int i = 0; i < n; i++){
        for (int j = 1; j <= m; j++){
            dp[i][j] = 0;
        }
    }

    if (a[0] != 0){
        dp[0][a[0]] = 1; // a[0] is fixed
    } else {
        for (int j = 1; j <= m; j++){
            dp[0][j] = 1; // all arrays of length 1 match 
        }
    }

    for (int i = 1; i < n; i++){
        // a[i] is unknown
        if (a[i] == 0){
            for (int j = 1; j <= m; j++){
                dp[i][j] = dp[i - 1][j] % MOD;
                // prev was down
                if (j != 1){
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
                } 
                // prev was up
                if (j != m){
                    dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % MOD;
                }
            }
        } 
        // a[i] is fixed 
        else {
            // all dp[i][j] are 0 except j == a[i]
            dp[i][a[i]] = dp[i-1][a[i]] % MOD;
            // prev was down
            if (a[i] != 1){
                dp[i][a[i]] = (dp[i][a[i]] + dp[i-1][a[i] - 1]) % MOD;
            }
            // prev was up
            if (a[i] != m){
                dp[i][a[i]] = (dp[i][a[i]] + dp[i-1][a[i] + 1]) % MOD;
            }
        }
    }
    int ans = 0;
    for (int j = 1; j <= m; j++){
        ans = (ans + dp[n - 1][j]) % MOD;
    }
    cout << ans;
}