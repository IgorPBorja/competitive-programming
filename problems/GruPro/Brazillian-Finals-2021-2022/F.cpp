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
#define print(msg, v) debug << msg; for(auto it = v.begin(); it != v.end(); it++){debug << *it << " ";} debug << endl;
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

const i64 INF = (i64)2e18;
void dfs(i64 u, const vector<vector<i64>>& adj, vector<i64>& vis, vector<i64>& cur){
    vis[u] = true;
    cur.emplace_back(u);
    for (i64 v: adj[u]){
        if (!vis[v]){
            dfs(v, adj, vis, cur);
        }
    }
}

void solve(){
    i64 n, m;
    cin >> n >> m;
    vector<vector<i64>> adj(n - 1);
    for (i64 i = 0; i < m; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        if (u < n - 1 && v < n - 1){
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
    }
    vector<pair<i64, vector<i64>>> components;
    vector<i64> vis(n - 1, false);

    for (i64 u = 0; u < n - 1; u++){
        if (!vis[u]){
            vector<i64> cur;
            dfs(u, adj, vis, cur);
            i64 msk = -INF;
            for (i64 v: cur) msk = max(msk, v);
            components.emplace_back(msk, cur);
        }
    }
    if (components.size() == 1){
        // N is not bridge
        for (i64 i = 0; i < n - 1; i++) cout << "B";
        cout << "A";
        cout << endl;
        return;
    } else {
        i64 argmax = 0, mx = components[0].first;
        for (i64 i = 1; i < components.size(); i++){
            if (components[i].first > mx){
                mx = components[i].first;
                argmax = i;
            }
        }
        auto largest = components[argmax].second;
        vector<char> assign(n, 'A');
        // if split into multiple components, then B can only take the largest one...
        for (i64 u: largest) assign[u] = 'B';
        for (char c: assign) cout << c;
        cout << endl;
    }
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
