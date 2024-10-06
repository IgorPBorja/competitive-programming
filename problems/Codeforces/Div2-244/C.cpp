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
#define printG(msg, G) cout << msg << endl; for (i64 u = 0; u < G.size(); u++) { printmsg("     adj[" << u << "]=", G[u].begin(), G[u].end()); }
 
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

const i64 MOD = (i64)1e9 + 7;
const i64 INF = 2e18;

namespace Kosaraju {
    void forward(i64 u, const vector<vector<i64>> &G, vector<bool> &vis, vector<i64> &post_order){
        vis[u] = true;
        for (i64 v: G[u]){
            if (!vis[v]){
                forward(v, G, vis, post_order);
            }
        }
        post_order.emplace_back(u);
    }

    void backward(i64 u, const vector<vector<i64>> &G, vector<bool> &vis, vector<i64> &comp, i64 c){
        vis[u] = true;
        comp[u] = c;
        for (i64 v: G[u]){
            if (!vis[v]){
                backward(v, G, vis, comp, c);
            }
        }
    }

    pair<vector<i64>, i64> scc(const vector<vector<i64>> &G){
        const i64 n = G.size();
        vector<vector<i64>> Gt(n);
        for (i64 u = 0; u < n; u++){
            for (i64 v: G[u]){
                Gt[v].emplace_back(u);
            }
        }
        vector<bool> vis(n, false);
        vector<i64> post_order;
        for (i64 u = 0; u < n; u++){
            if (!vis[u]) forward(u, G, vis, post_order);
        }

        vector<i64> reverse_post_order = post_order;
        reverse(reverse_post_order.begin(), reverse_post_order.end());
        fill(vis.begin(), vis.end(), false);

        vector<i64> comp(n, -1);
        i64 c = 0;
        for (i64 u: reverse_post_order){
            if (!vis[u]) {
                backward(u, Gt, vis, comp, c);
                ++c;
            }
        }
        return {comp, c};
    }
};

void solve(){
    i64 n, m;

    cin >> n;
    i64 cost[n];
    for (i64 i = 0; i < n; i++) cin >> cost[i];

    cin >> m;
    vector<vector<i64>> G(n);
    for (i64 i = 0; i < m; i++){
        i64 a, b;
        cin >> a >> b;
        G[--a].emplace_back(--b);
    }

    auto[comp, num_comps] = Kosaraju::scc(G);
    vector<i64> min_cost(num_comps, INF);
    vector<i64> ways(num_comps, 0);

    for (i64 i = 0; i < n; i++){
        if (min_cost[comp[i]] == cost[i]){
            ++ways[comp[i]];
        } else if (min_cost[comp[i]] > cost[i]){
            min_cost[comp[i]] = cost[i];
            ways[comp[i]] = 1;
        }
    }

    i64 min_total_cost = accumulate(min_cost.begin(), min_cost.end(), (i64)0);
    i64 total_ways = 1;
    for (i64 w: ways){
        total_ways = (total_ways * w) % MOD;
    }
    cout << min_total_cost << " " << total_ways << endl;
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
