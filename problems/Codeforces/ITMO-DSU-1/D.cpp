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

template <typename T1, typename T2, typename T3>
ostream& operator<< (ostream& out, tuple<T1, T2, T3> x)
{
	out << get<0>(x) << " " << get<1>(x) << " " << get<2>(x);
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

struct DSU {
	vector<i64> parent, sz;

	DSU(i64 n){
		parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
		sz.assign(n, 1);
	}

	i64 find(i64 x){
		if (parent[x] != x){
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	bool same(i64 x, i64 y){
		return find(x) == find(y);
	}
	
	void merge(i64 x, i64 y){
		x = find(x), y = find(y);
		if (x == y) return;
		if (sz[x] > sz[y]) swap(x, y);

		sz[y] += sz[x];
		parent[x] = y;
	}
};

void solve(){
	#define CUT_MODE 1
	#define ASK_MODE 2

	i64 n, m, q;
	cin >> n >> m >> q;

	vector<pair<i64, i64>> to_cut;
	vector<pair<i64, i64>> edges(m);
	tuple<i64, i64, i64> queries[q];

	for (i64 i = 0; i < m; i++){
		i64 a, b;
		cin >> a >> b;
		--a; --b;
		edges.emplace_back(a, b);
	}
	
	for (i64 i = 0; i < q; i++){
		string action;
		i64 a, b;
		cin >> action;
		cin >> a >> b;
		--a; --b;
		queries[i] = { (action == "cut") ? CUT_MODE : ASK_MODE, a, b };
		if (action == "cut"){
			to_cut.emplace_back(a, b);
		}
	}

	// printmsg("queries=", queries, queries + sizeof(queries) / sizeof(tuple<i64, i64, i64>));

	DSU dsu(n);
	vector<pair<i64, i64>> sorted_cuts = to_cut;
	sort(sorted_cuts.begin(), sorted_cuts.end());
	for (auto[a, b]: edges){
		if (
			(lower_bound(sorted_cuts.begin(), sorted_cuts.end(), make_pair(a, b)) == sorted_cuts.end())
			&& 
			(lower_bound(sorted_cuts.begin(), sorted_cuts.end(), make_pair(b, a)) == sorted_cuts.end())
		){
			dsu.merge(a, b);
		}
	}

	vector<string> ans;
	for (i64 i = q - 1; i >= 0; i--){
		auto[mode, a, b] = queries[i];
		if (mode == CUT_MODE){
			dsu.merge(a, b);
		} else {
			ans.emplace_back(dsu.same(a, b) ? "YES" : "NO");
		}
	}
	reverse(ans.begin(), ans.end());
	for (string s: ans){
		cout << s << endl;
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
