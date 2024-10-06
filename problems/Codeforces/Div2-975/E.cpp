#define TESTCASES
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

// suppose we want to keep leaves only at depth d
// then we remove all nodes with depth d' > d
// and all nodes with max_depth < d (since those only see leaves ending before cutoff)
// where max_depth(u) = max(depth(v) : v is in the subtree rooted at u, including u)
// those two sets do not overlap

vector<vector<i64>> root(const vector<vector<i64>>& tree, i64 r){
	// bfs 
	queue<i64> q;
	q.emplace(r);
	const i64 n = tree.size();
	vector<vector<i64>> dag(tree.size());
	vector<bool> vis(n, false);
	while (!q.empty()){
		auto u = q.front();
		q.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (i64 v: tree[u]){
			if (!vis[v]){
				dag[u].emplace_back(v);
				q.emplace(v);
			}
		}
	}
	return dag;
} 

void dfs(const vector<vector<i64>>& dag, i64 u, i64 d, vector<i64>& max_depth, vector<i64>& depth){
	max_depth[u] = d;
	depth[u] = d;
	for (i64 v: dag[u]){
		dfs(dag, v, d + 1, max_depth, depth);
		max_depth[u] = max(max_depth[u], max_depth[v]);
	}
}

void solve(){
	i64 n;
	cin >> n;
	vector<vector<i64>> tree(n);
	for (i64 i = 0; i < n - 1; i++){
		i64 u, v;
		cin >> u >> v;
		--u; --v;
		tree[u].emplace_back(v);
		tree[v].emplace_back(u);
	}
	vector<vector<i64>> dag = root(tree, 0);
	vector<i64> max_depth(n), depth(n);
	dfs(dag, 0, 0, max_depth, depth);

	vector<i64> cnt_d(n), cnt_max_d(n);
	for (i64 i = 0; i < n; i++){
		++cnt_d[depth[i]];
		++cnt_max_d[max_depth[i]];
	}
	// prefix max depth, suffix depth
	vector<i64> p = cnt_max_d, s = cnt_d;
	for (i64 i = 1; i < n; i++){
		p[i] += p[i - 1];
	}
	for (i64 i = n - 2; i >= 0; i--){
		s[i] += s[i + 1];
	}

	i64 rem = n - 1;
	for (i64 d = n - 1; d >= 0; d--){
		// we can't leave at d if there are no nodes at d
		if (cnt_d[d] == 0) continue;
		i64 lo = (d > 0) ? p[d - 1] : 0;  // shallow branches
		i64 hi = (d < n - 1) ? s[d + 1] : 0;  // deep nodes
		rem = min(rem, lo + hi);
	}
	cout << rem << endl;
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
