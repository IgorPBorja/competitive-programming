// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
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


void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++) cin >> a[i];

    i64 m;
    cin >> m;
    i64 b[m];
    for (i64 i = 0; i < m; i++) cin >> b[i];

    i64 dp[n][m];
    pair<i64, i64> prev[n][m];
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            prev[i][j] = make_pair(-1, -1);
        }
    }
    for (i64 j = 0; j < m; j++){
        dp[0][j] = ((a[0] == b[j]) ? 1 : 0);
    }

    vector<i64> matches[n];
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            if (a[i] == b[j]){
                matches[i].emplace_back(j);
            }
        }
    }

    for (i64 i = 1; i < n; i++){
        for (i64 j = 0; j < m; j++){
            if (a[i] != b[j]){
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = 1;
            for (i64 i2 = 0; i2 < i; i2++){
                if (a[i2] >= a[i]) continue;  // not increasing
                for (i64 j2: matches[i2]){
                    if (j2 >= j) break;  // after j
                    if (1 + dp[i2][j2] > dp[i][j]){
                        dp[i][j] = 1 + dp[i2][j2];
                        prev[i][j] = make_pair(i2, j2);
                    }
                }
            }
        }
    }
    
    i64 ans = 0;
    pair<i64, i64> best = make_pair(-1, -1);
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            if (dp[i][j] > ans){
                ans = dp[i][j];
                best = make_pair(i, j);
            }
        }
    }
    cout << ans << endl;
    vector<i64> seq;
    for (i64 _ = 0; _ < ans; _++){
        seq.emplace_back(a[best.first]);
        best = prev[best.first][best.second];
    }
    reverse(seq.begin(), seq.end());
    for (auto x: seq){
        cout << x << " ";
    }
    cout << endl;
}
 
signed main(){
	fastio;
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
	int t;
#ifdef TESTCASES
	cin >> t;
#else
	t = 1;
#endif
	while (t--){
		solve();
	}
}
