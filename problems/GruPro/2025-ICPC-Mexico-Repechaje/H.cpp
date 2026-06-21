#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define printgraph(msg, G) \
    cerr << msg << endl; \
    for (i64 u = 0; u < (i64)G.size(); u++){ \
        cerr << "  u=" << u << "->"; \
        for (i64 v: G[u]) { cerr << v << " "; } \
        cerr << endl; \
    } \


#define i64 int64_t

/*
dp[b][i][j] = max sum of consecutive subarray ending at j using at most i flips
                where b is a flag (b=1 if j is flipped on i-th flip, else 0)
*/

template<typename T>
T max3(T a, T b, T c){
    return max(a, max(b, c));
}

const i64 MAXN = (i64)1e5 + 1;
const i64 MAXK = 101;
i64 dp[2][MAXK + 1][MAXN + 1];
// array<array<i64, MAXN + 1>, MAXK + 1> dp[2];
const i64 INF = 1e15;

signed main(){
    i64 n, k;
    cin >> n >> k;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++) cin >> a[i];
    
    dp[0][0][0] = a[0];
    for (i64 j = 1; j < n; j++){
        dp[0][0][j] = max(dp[0][0][j - 1], (i64)0) + a[j];
        dp[1][0][j] = -INF;  // can't be flipped without flip
    }
    for (i64 i = 1; i <= k; i++){
        dp[0][i][0] = a[0];  // no flip
        if (i == 1){
            dp[1][i][0] = -a[0];  // forced 1 flip
        } else {
            dp[1][i][0] = abs(a[0]);  // even or odd flips
        }
        for (i64 j = 1; j < n; j++){
            dp[0][i][j] = max3(
                dp[0][i - 1][j],  // don't flip this time
                dp[1][i - 1][j],  // don't flip this time
                max3(dp[0][i][j - 1], dp[1][i][j - 1], (i64)0) + a[j]  // flip before
            );
            dp[1][i][j] = max(
                dp[1][i - 1][j],  // don't flip this time, but previous flip covers j
                max3(
                    dp[1][i][j-1],  // last flip starts before j
                    max(dp[0][i-1][j-1], dp[1][i-1][j-1]),  // last flip starts at j
                    (i64)0
                ) - a[j]  // flip at suffix
            );
        }
    }
    i64 ans = -INF;
    for (i64 j = 0; j < n; j++){  // trying best subarray ending at j with at most k flips
        ans = max3(ans, dp[0][k][j], dp[1][k][j]);
    }
    // printgraph("dp[0]=", dp[0]);
    // printgraph("dp[1]=", dp[0]);
    cout << ans << endl;
}