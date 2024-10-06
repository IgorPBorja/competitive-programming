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
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

struct LCA {
	LCA(const vector<vector<i64>> &adj){
		set_parents(adj);
		blift();
	}	

	i64 jump(i64 u, i64 k){
		for (i64 i = 0; i <= ilog && u != -1; i++){
			if ((k >> i) & 1){
				u = b[i][u];
			}
		}
		return u;
	}

	LCA(const vector<i64> &parents){
		const i64 n = parents.size();
		vector<vector<i64>> adj(n);
		for (i64 i = 0; i < parents.size(); i++){
			if (parents[i] != -1){
				adj[parents[i]].emplace_back(i);
			}
		}
		set_parents(adj);
		blift();
	}

	i64 lca(i64 u, i64 v){
		if (h[u] > h[v]) swap(u, v);
		v = jump(v, h[v] - h[u]);

		if (u == v){
			return u;
		}

		// loop invariant: not yet at common ancestor
		for (i64 i = ilog; i >= 0; i--){
			if (b[i][u] != b[i][v]){
				u = b[i][u];
				v = b[i][v];
			}
		}
		return p[u];
	}

private:
	vector<i64> p, h;
	vector<vector<i64>> b;
	i64 ilog;

	void set_parents(const vector<vector<i64>> &adj){
		const i64 n = adj.size();
		p.assign(n, -1);
		h.resize(n);
		for (i64 i = 0; i < n; i++){
			if (p[i] == -1){
				dfs(i, adj);
			}
		}
	}

	void dfs(i64 u, const vector<vector<i64>> &adj, i64 d = 0, i64 par = -1){
		h[u] = d;
		p[u] = par;
		for (i64 v: adj[u]){
			if (v == par) continue;
			dfs(v, adj, d + 1, u);
		}
	}

	void blift() {
		const i64 n = p.size();
		ilog = 0;
		while ((1ll << (ilog + 1)) <= n){
			++ilog;
		}
		b.assign(ilog + 1, vector<i64>(n, -1));
		for (i64 i = 0; i < n; i++){
			b[0][i] = p[i];
		}
		
		for (i64 i = 1; i <= ilog; i++){
			for (i64 j = 0; j < n; j++){
				if (b[i - 1][j] != -1){
					b[i][j] = b[i - 1][b[i - 1][j]];
				}
			}
		}
	}
};

void solve(){
	i64 n, q;
	cin >> n >> q;
	vector<i64> parents(n);

	parents[0] = -1;
	for (i64 i = 0; i < n - 1; i++){
		cin >> parents[i + 1];
		// --parents[i + 1];  // to 0-index (not needed in this question)
	}
	
	LCA lca(parents);
	for (i64 i = 0; i < q; i++){
		i64 a, b;
		cin >> a >> b;
		// --a; --b;  // to 0-index (not needed in this question)
		cout << lca.lca(a, b) << endl;
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
