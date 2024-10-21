// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 MAXN = (i64)1e5 + 10;
i64 dp[2][MAXN];

void solve(){
    i64 n;
    cin >> n;

    i64 a[2][n];
    for (i64 i = 0; i < 2; i++){
        for (i64 j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    dp[0][0] = a[0][0];
    dp[1][0] = a[1][0];
    for (i64 i = 1; i < n; i++){
        i64 h0 = dp[1][i - 1] + a[0][i];
        i64 h1 = dp[0][i - 1] + a[1][i];
        dp[0][i] = max(dp[0][i - 1], h0);
        dp[1][i] = max(dp[1][i - 1], h1);
    }
    // printmsg("dp[0]=", dp[0], dp[0] + n);
    // printmsg("dp[1]=", dp[1], dp[1] + n);
    cout << max(dp[0][n - 1], dp[1][n - 1]) << endl;
}

signed main(){
    fastio;
    int t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--){
        solve();
    }
}


