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


void solve(){
	i64 n;
	cin >> n;

	vector<vector<i64>> g(n);
	for (i64 i = 0; i < n - 1; i++){
		i64 a, b;
		cin >> a >> b;
		--a; --b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	i64 sequence[n];
	for (i64 i = 0; i < n; i++){
		cin >> sequence[i];
		--sequence[i];
	}
	// MUST start from vertex 1 (or 0 in 0-indexing)
	if (sequence[0] != 0){
		cout << "NO" << endl;
		return;
	}

	queue<pair<i64, i64>> q;
	// add a virtual edge to solve the weird corner case where from the root you don't need
	// to discard an edge, but from an intermediate vertex you have to
	g[0].emplace_back(-1);

	q.emplace(-1, sequence[0]);
	i64 first_idx = 1;
	while (!q.empty()){
		auto[parent, u] = q.front();
		q.pop();
		set<i64> s1, s2;
		for (i64 v: g[u]){
			if (v != parent) s1.insert(v);
		}
		for (i64 i = 0; i < g[u].size() - 1; i++){
			s2.insert(sequence[first_idx + i]);
			q.emplace(u, sequence[first_idx + i]);
		}
		if (s1 != s2){
			cout << "NO" << endl;
			return;
		} 
		first_idx += g[u].size() - 1;
	}
	cout << "YES" << endl;
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
