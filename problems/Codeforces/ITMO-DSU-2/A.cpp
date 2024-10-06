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

struct DSU {
	vector<i64> p, sz, max_v;

	DSU(i64 n){
		p.resize(n);
		sz.assign(n, 1);
		max_v.resize(n);

		iota(p.begin(), p.end(), 0);
		iota(max_v.begin(), max_v.end(), 0);
	}

	i64 find(i64 x){
		if (p[p[x]] != p[x]){
			p[x] = find(p[x]);
		}
		return p[x];
	}

	void merge(i64 x, i64 y){
		x = find(x), y = find(y);
		if (x == y) return;
		if (sz[x] > sz[y]) swap(x, y);

		p[x] = y;
		sz[y] += sz[x];
		max_v[y] = max(max_v[y], max_v[x]);
	}

	i64 query(i64 x){
		return max_v[find(x)];
	}
};

void solve(){
	i64 n, m;
	cin >> n >> m;

	DSU dsu(n + 1);
	for (i64 i = 0; i < m; i++){
		string mode;
		i64 p;
		cin >> mode >> p;
		--p;
		if (mode == "-"){
			dsu.merge(p, p + 1);
		} else {
			i64 ans = dsu.query(p) + 1;
			cout << ((ans <= n) ? ans : -1) << endl;
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
