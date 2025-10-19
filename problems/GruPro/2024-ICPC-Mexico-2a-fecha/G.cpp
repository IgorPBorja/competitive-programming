// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		cerr << "G[" << u << "]="; \
		for (i64 v: G[u]) { \
			cerr << v << " "; \
		} \
		cerr << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

void dfs1(i64 u, const vector<vector<i64>>& adj, vector<i64>& subtree, i64 p = -1){
    subtree[u] = 1;
    for (i64 v: adj[u]){
        if (v == p) continue;
        dfs1(v, adj, subtree, u);
        subtree[u] += subtree[v];
    }
}

void dfs2(i64 u, const vector<vector<i64>>& adj, const vector<i64>& subtree, i64& best, i64& best_cnt, i64 p = -1){
    const i64 n = adj.size();
    for (i64 v: adj[u]){
        if (v == p) continue;
        // look at u->v
        // (n-T[v]) * T[v]
        i64 score = (n - subtree[v]) * subtree[v];
        if (score > best){
            best = score;
            best_cnt = 1;
        } else if (score == best){
            ++best_cnt;
        }
        dfs2(v, adj, subtree, best, best_cnt, u);
    }
}

void solve(){
    i64 n;
    cin >> n;
    vector<i64> subtree(n, 0);
    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs1(0, adj, subtree);

    i64 best_cnt = 0, best = -1;
    dfs2(0, adj, subtree, best, best_cnt);
    cout << best << " " << best_cnt << endl;
}
 
signed main(){
	fastio;
	int t = 1;
#ifdef TESTCASES
	cin >> t;
#endif
	while (t--){
		solve();
	}
}
