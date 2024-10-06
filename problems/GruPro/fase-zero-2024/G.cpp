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
 
#define print(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

const i64 INF = 1e15;

struct MinTree {
	vector<i64> seg;
	i64 n;

	MinTree(i64 n) : n(n) {
		seg.assign(4 * n, INF);
	}

	i64 query(i64 l, i64 r){
		return _query(l, r, 0, n - 1, 0);
	}

	void update(i64 p, i64 x){
		_update(p, x, 0, n - 1, 0);
	}
private:
	i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
		i64 tm = tl + (tr - tl) / 2;
		if (l == tl && r == tr){
			return seg[node];
		} else if (r <= tm){
			return _query(l, r, tl, tm, 2 * node + 1);
		} else if (l > tm){
			return _query(l, r, tm + 1, tr, 2 * node + 2);
		} else {
			return min(_query(l, tm, tl, tm, 2 * node + 1), _query(tm + 1, r, tm + 1, tr, 2 * node + 2));
		}
	}

	void _update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
		i64 tm = tl + (tr - tl) / 2;
		if (tl == p && p == tr){
			seg[node] = x;
		} else {
			if (p <= tm){
				_update(p, x, tl, tm, 2 * node + 1);
			} else {
				_update(p, x, tm + 1, tr, 2 * node + 2);
			}
			seg[node] = min(seg[2 * node + 1], seg[2 * node + 2]);
		}
	}
};

void solve(){
	i64 n, k;
	cin >> n >> k;

	i64 a[n + 1], b[n + 1];
	for (i64 i = 0; i < n; i++){
		cin >> a[i + 1];
	}
	for (i64 i = 0; i < n; i++){
		cin >> b[i + 1];
	}
	a[0] = 0; b[0] = k;

	MinTree seg(n);	
	vector<i64> dp(n, INF);
	for (i64 i = n - 1; i >= 0; i--){
		// check for last position I can go to using only the fuel for b[i]
		// without stopping
		i64 j = (upper_bound(a, a + n + 1, a[i] + b[i]) - a) - 1; // up to a[n] = *(a + n)
		if (j == n){
			seg.update(i, 0);
			dp[i] = 0;
		} else if (j > i){ // and j < n
			i64 subsolve = seg.query(i + 1, j);
			if (subsolve < INF) {
				seg.update(i, 1 + subsolve);
				dp[i] = 1 + subsolve;
			}
		}
	}
	// print("seg=", seg.seg.begin(), seg.seg.end());
	// print("dp=", dp.begin(), dp.end());
	if (dp[0] < INF){
		cout << dp[0] << endl;
	} else {
		cout << -1 << endl;
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
