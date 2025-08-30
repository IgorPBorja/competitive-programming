// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
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

i64 c;
const i64 MOD = (i64)1e9 + 7;

void dfs(i64 u, const vector<vector<i64>>& adj, vector<i64>& order, vector<i64>& vis){
    vis[u] = true;
    for (i64 v: adj[u]){
        if (!vis[v]){
            dfs(v, adj, order, vis);
        }
    }
    order[u] = c--;
}

void solve(){
    i64 n, m;
    cin >> n >> m;
    vector<vector<i64>> dag(n), rev_dag(n);
    for (i64 i = 0; i < m; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        dag[u].emplace_back(v);
        rev_dag[v].emplace_back(u);
    }
    for (i64 u = 0; u < n; u++) sort(all(dag[u]));

    c = n;
    i64 start = -1;
    for (i64 u = 0; u < n; u++){
        if (rev_dag[u].empty()){
            start = u;
            break;
        }
    }
    if (start == -1){
        cout << -1 << endl;
        return;
    }
    vector<i64> order(n, -1), vis(n, false);
    dfs(start, dag, order, vis);
    vector<pair<i64, i64>> ordered_pairs(n);
    for (i64 u = 0; u < n; u++) ordered_pairs[u] = make_pair(order[u], u);
    sort(all(ordered_pairs));
    // assert no cycles
    bool ok = true;
    for (i64 u = 0; u < n; u++){
        for (i64 v: dag[u]){
            if (order[u] > order[v]){
                ok = false;
            }
        }
    }
    if (!ok){
        cout << -1 << endl;
        return;
    }
    for (auto[_, u]: ordered_pairs){
        cout << u + 1 << " ";
    }
    cout << endl;
}
 
signed main(){
	fastio;
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
