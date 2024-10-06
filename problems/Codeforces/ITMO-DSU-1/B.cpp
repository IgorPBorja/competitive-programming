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

struct DSU {
	vector<i64> parent, sz, minv, maxv;

	DSU(i64 n){
		parent.resize(n);
		minv.resize(n);
		maxv.resize(n);
		iota(parent.begin(), parent.end(), 0);
		iota(minv.begin(), minv.end(), 0);
		iota(maxv.begin(), maxv.end(), 0);
		sz.assign(n, 1);
	}

	i64 find(i64 x){
		if (parent[x] != x){
			parent[x] = find(parent[x]);  // path-compression
		}
		return parent[x];
	}

	i64 min(i64 x){
		return minv[find(x)];
	}

	i64 max(i64 x){
		return maxv[find(x)];
	}

	i64 size(i64 x){
		return sz[find(x)];
	}

	void unite(i64 x, i64 y){
		x = find(x);
		y = find(y);
		if (x == y){
			return;
		} else if (sz[x] > sz[y]) {
			swap(x, y);
		}
		sz[y] += sz[x];
		parent[x] = y;
		minv[y] = std::min(minv[y], minv[x]);
		maxv[y] = std::max(maxv[y], maxv[x]);
	}
};

void solve(){
	i64 n, m;
	cin >> n >> m;

	DSU dsu(n);
	for (i64 i = 0; i < m; i++){
		string action;
		i64 u, v;
		cin >> action >> u;
		--u;
		if (action == "get"){
			cout << dsu.min(u) + 1 << " " << dsu.max(u) + 1 << " " << dsu.size(u) << endl;
		} else {
			cin >> v;
			--v;
			dsu.unite(u, v);
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
