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
const i64 INF = 1e18;

namespace Tarjan {
    vector<i64> lowlink, t_in;
    vector<bool> on_path;
    vector<i64> stack;
    vector<i64> _scc;
    i64 scc_counter = 0;

    i64 timer;

    void dfs(i64 u, const vector<vector<i64>>& adj, i64 p){
        lowlink[u] = t_in[u] = timer++;
        stack.emplace_back(u);
        on_path[u] = true;
        // for all backedges update by t_in of the back node
        // for all tree edges: descend then update with its lowlink
        for (i64 v: adj[u]){
            if (on_path[v]){
                lowlink[u] = min(lowlink[u], t_in[v]);
            } else if (t_in[v] == INF) {
                dfs(v, adj, u);
                lowlink[u] = min(lowlink[u], lowlink[v]);
            }
        }
        // starts SCC (first visited of the SCC)
        if (lowlink[u] == t_in[u]){
            while (stack.back() != u){
                i64 w = stack.back();
                _scc[w] = scc_counter;
                stack.pop_back();
                on_path[w] = false;
            }
            _scc[u] = scc_counter;
            stack.pop_back();
            on_path[u] = false;

            ++scc_counter;
        }
    }

    vector<i64> scc(const vector<vector<i64>>& adj){
        const i64 n = adj.size();
        lowlink.resize(n);
        t_in.assign(n, INF);
        on_path.assign(n, false);
        _scc.resize(n);
        timer = 0;
        for (i64 u = 0; u < n; u++){
            if (t_in[u] == INF){
                dfs(u, adj, -1);
            }
        }
        return _scc;
    }
}

void solve(){
    i64 n, m;
    cin >> n >> m;
    vector<vector<i64>> adj(n);

    for (i64 i = 0; i < m; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].emplace_back(b);
    }

    vector<i64> sccs = Tarjan::scc(adj);
    cout << *max_element(sccs.begin(), sccs.end()) + 1 << endl;
    for (i64 x: sccs){
        cout << x + 1 << " ";
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
