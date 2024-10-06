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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

vector<vector<i64>> g;
vector<vector<i64>> levels;
vector<i64> ptrs;

void rebuild(i64 d, i64 k){
	i64 u = levels[d][ptrs[d]];
	++ptrs[d];
	if (d + 1 == levels.size()){
		return;  // reached maximum distance
	} 
	i64 deg = (d == 0) ? 0 : 1;  // if it's not root then there is a parent
	while (deg < k && ptrs[d + 1] < levels[d + 1].size()){
		i64 v = levels[d + 1][ptrs[d + 1]];
		g[u].emplace_back(v);
		g[v].emplace_back(u);
		++deg;
		rebuild(d + 1, k);
	}
}

void solve(){
	i64 n, k;
	cin >> n >> k;

	levels = vector<vector<i64>>(n);
	g = vector<vector<i64>>(n);
	ptrs = vector<i64>(n, 0);

	i64 d_i;
	for (i64 i = 0; i < n; i++){
		cin >> d_i;
		levels[d_i].emplace_back(i);
	}
	if (levels[0].size() != 1){
		cout << -1 << endl;
		return;
	}
	rebuild(0, k);

	i64 e = 0;
	for (i64 u = 0; u < n; u++) e += g[u].size();
	e /= 2; // undirected
	
	// the result of rebuild should be a tree
	if (e != n - 1){
		cout << -1 << endl;
		return;
	}

	cout << n - 1 << endl;

	for (i64 u = 0; u < n; u++){
		for (i64 v: g[u]){
			if (u < v){
				// guarantees each edge will only appear once
				cout << u + 1 << " " << v + 1 << endl;  // the +1 is for 1-indexing
			}
		}
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
