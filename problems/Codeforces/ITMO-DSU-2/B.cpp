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

i64 clock_last(i64 i, i64 x1, i64 x2, i64 mod){
	i64 deltas[2] = {
		(mod + (x1 % mod) - (i % mod)) % mod,
		(mod + (x2 % mod) - (i % mod)) % mod
	};
	return (deltas[0] >= deltas[1]) ? x1 : x2;
}

struct CircularDSU {
	vector<i64> p, sz, next;
	const i64 n;

	CircularDSU(i64 n) : n(n) {
		p.resize(n);
		sz.assign(n, 1);
		next.resize(n);

		iota(p.begin(), p.end(), 0);
		iota(next.begin(), next.end(), 0);
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

		i64 last = next[y];  // path is directed: x -> y
		if (sz[x] > sz[y]) swap(x, y);
		p[x] = y;
		sz[y] += sz[x];

		next[y] = last;
	}

	i64 query(i64 x){
		return next[find(x)];
	}
};

void solve(){
	i64 n;
	cin >> n;

	CircularDSU dsu(n);
	for (i64 i = 0; i < n; i++){
		i64 p;
		cin >> p;
		--p;
		i64 next = dsu.query(p);
		cout << next + 1 << " ";
		dsu.merge(p, (next + 1) % n);
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
