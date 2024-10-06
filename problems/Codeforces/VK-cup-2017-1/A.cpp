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

pair<vector<i64>, vector<i64>> components(vector<vector<i64>> &g){
	vector<i64> comp(g.size(), -1);
	vector<i64> comp_sizes;
	for (i64 src = 0; src < g.size(); src++){
		i64 s = 0;
		if (comp[src] != -1) continue;
		queue<i64> q;
		q.emplace(src);
		while (!q.empty()){
			i64 u = q.front();
			q.pop();
			if (comp[u] != -1) continue;
			comp[u] = comp_sizes.size();
			++s;
			for (i64 v: g[u]){
				if (comp[v] == -1){
					q.emplace(v);
				}
			}
		}
		comp_sizes.emplace_back(s);
	}
	return {comp, comp_sizes};
}

void solve(){
	i64 n, m;
	cin >> n >> m;

	vector<set<i64>> __g(n);
	for (i64 i = 0; i < m; i++){
		i64 a, b;
		cin >> a >> b;
		--a; --b;
		__g[a].insert(b);
		__g[b].insert(a);
	}
	vector<vector<i64>> g(n);
	for (i64 i = 0; i < n; i++){
		g[i] = vector<i64>(__g[i].begin(), __g[i].end());
	}

	auto[comp, comp_sizes] = components(g);

	// each component must be a complete graph
	bool ok = true;
	for (i64 i = 0; i < n; i++){
		ok = ok & (g[i].size() == comp_sizes[comp[i]] - 1);
	}
	if (ok){
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
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
