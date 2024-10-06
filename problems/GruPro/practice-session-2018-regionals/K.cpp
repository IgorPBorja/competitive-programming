// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
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

const i64 MAXN = 5e4;
i64 dp[MAXN + 1];
i64 a[MAXN + 1];
i64 p[MAXN + 2];

void solve(){
    i64 n;
    cin >> n;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    // prefix it
    p[0] = 0;
    for (i64 i = 0; i < n; i++){
        p[i + 1] = p[i] + a[i];
    }
    // for starting position i
    for (i64 i = 0; i < n; i++){
        i64 ans = 0;
        i64 turn = 1;
        for (i64 j = i; j < n; j += 3 * turn, turn++){
            // [j, ..., min(n - 1, j + 3 * turn - 1)]
            ans += max(p[min(n, j + 3 * turn)] - p[j], (i64)0);
        }
        cout << ans << endl; 
    }
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
