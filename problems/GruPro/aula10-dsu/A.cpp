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
	vector<i64> p, sz;
	i64 components;

	DSU(i64 n) : components(n) {
		p.resize(n);
		iota(p.begin(), p.end(), 0);
		sz.assign(n, 1);
	}

	i64 find(i64 x){
		return (p[x] != x) ? (p[x] = find(p[x])) : p[x];
	}

	void merge(i64 x, i64 y){
		x = find(x), y = find(y);
		if (x == y) return;
		if (sz[x] > sz[y]) swap(x, y);
		sz[y] += sz[x];
		p[x] = y;
		--components;
	}
};

void solve(){
	// for each l solve in decreasing order of r in O(m log(n))
	// total complexity: O(m^2 log(n))
	i64 n, m;
	cin >> n >> m;

	vector<pair<i64, i64>> e(m);	
	for (i64 i = 0; i < m; i++){
		i64 a, b;
		cin >> a >> b;
		--a; --b;
		e[i] = {a, b};
	}

	i64 k;
	cin >> k;
	vector<vector<pair<i64, i64>>> queries_per_start(m);
	vector<i64> ans(k);
	for (i64 i = 0; i < k; i++){
		i64 l, r;
		cin >> l >> r;
		--l; --r;
		queries_per_start[l].emplace_back(r, i);
	}
	for (i64 l = 0; l < m; l++){
		sort(queries_per_start[l].begin(), queries_per_start[l].end());
		reverse(queries_per_start[l].begin(), queries_per_start[l].end());
	}

	for (i64 l = 0; l < m; l++){
		i64 r = m - 1;  // last element excluded
		DSU d(n);
		for (i64 j = 0; j < l; j++){
			d.merge(e[j].first, e[j].second);
		}
		for (auto[r_i, i]: queries_per_start[l]){
			for (; r > r_i; r--){
				d.merge(e[r].first, e[r].second);
			}
			ans[i] = d.components;
		}
	}
	for (i64 i = 0; i < k; i++){
		cout << ans[i] << endl;
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
