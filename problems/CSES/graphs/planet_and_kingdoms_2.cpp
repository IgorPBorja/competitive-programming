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

void dfs1(i64 u, const vector<vector<i64>> &adj, vector<bool> &vis, vector<i64> &stack){
    vis[u] = true;
    for (i64 v: adj[u]){
        if (!vis[v]){
            dfs1(v, adj, vis, stack);
        }
    }
    stack.emplace_back(u);
}

void dfs2(i64 u, const vector<vector<i64>> &rev_adj, vector<bool> &vis, vector<i64> &scc, i64 k){
    scc[u] = k;
    vis[u] = true;
    for (i64 v: rev_adj[u]){
        if (!vis[v]){
            dfs2(v, rev_adj, vis, scc, k);
        }
    }
}

void solve(){
    i64 n, m;
    cin >> n >> m;
    vector<vector<i64>> adj(n);
    vector<vector<i64>> rev_adj(n);

    for (i64 i = 0; i < m; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].emplace_back(b);
        rev_adj[b].emplace_back(a);
    }

    vector<bool> vis(n, false);
    vector<i64> stack;
    for (i64 u = 0; u < n; u++){
        if (!vis[u]) dfs1(u, adj, vis, stack);
    }
    fill(vis.begin(), vis.end(), false);
    i64 scc_counter = 1;
    vector<i64> scc(n);

    reverse(stack.begin(), stack.end());

    for (i64 u: stack){
        if (!vis[u]){
            dfs2(u, rev_adj, vis, scc, scc_counter);
            ++scc_counter;
        }
    }
    cout << *max_element(scc.begin(), scc.end()) << endl;

    for (i64 i: scc){
        cout << i << " ";
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
