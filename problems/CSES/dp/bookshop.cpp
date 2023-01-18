#include <bits/stdc++.h>
using namespace std;
#define INF (int)(2e9)
// #define int long long
#define mod (int)(1e9 + 7)
#define vi vector<int>
#define vvi vector<vector<int>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define fi first
#define sec second
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL)
#define eb emplace_back
#define pb push_back
#define pop pop_back

int main(){
    fastio();

    int n, x;
    cin >> n >> x;
    int p[n], qtd[n];
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> qtd[i];
    vvi dp(n+1, vi(x+1, 0));

    // order of loops does not matter for correct output (ONLY TIME)!
    // for i = n-1..0 for m=0..x+1 is faster then the other way
    for (int i = n-1; i >= 0; i--){
        for (int m = 0; m < x+1; m++){
            dp[i][m] = max(dp[i][m], dp[i+1][m]); // dont grab p[i]
            if (p[i] <= m){
                dp[i][m] = max(dp[i+1][m], qtd[i] + dp[i+1][m - p[i]]);
            }
        }
    }
    cout << dp[0][x];
}