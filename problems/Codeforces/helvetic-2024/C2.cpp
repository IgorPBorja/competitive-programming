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
 
#define print(vec) for(auto x: vec){cerr << x << "|";} cerr << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

bool wins(vector<vector<i64>> &tree, i64 x, i64 p = -1){
	bool ok = false;
	for (i64 y: tree[x]){
		if (y == p) continue;
		ok = ok || !wins(tree, y, x);
	}
	return ok;
}

void solve(){
	i64 n, t;
	cin >> n >> t;

	vector<vector<i64>> adj(n);
	i64 u, v;
	for (i64 i = 0; i < n - 1; i++){
		cin >> u >> v;
		--u; --v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	// for (i64 i = 0; i < n; i++){
	// 	cerr << "i=" << i << ": -->";
	// 	print(adj[i]);
	// }

	// get idx
	i64 k;
	cin >> k;
	--k; // to 0-index
	if (wins(adj, k)){
		// first player always loses
		cout << "Ron" << endl;
	} else {
		cout << "Hermione" << endl;
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
