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

namespace Graph {
    i64 c;

    void dfs(i64 u, vector<vector<i64>> &G, vector<bool> &vis, vector<i64> &order){
        vis[u] = true;
        for (i64 v: G[u]){
            if (!vis[v]){
                dfs(v, G, vis, order);
            }
        }
        order[u] = c;
        --c;
    }

    vector<i64> toposort(vector<vector<i64>> &G){
        c = G.size() - 1;
        const i64 n = G.size();
        vector<bool> vis(n, false);
        vector<i64> order(n);
        for (i64 u = 0; u < n; u++){
            if (!vis[u]){
                dfs(u, G, vis, order);
            }
        }
        // validate order
        for (i64 u = 0; u < n; u++){
            for (i64 v: G[u]){
                if (order[u] >= order[v]) {
                    return vector<i64>();
                }
            }
        }
        return order;
    }
}

void solve(){
    i64 n;
    cin >> n;

    string names[n];
    for (i64 i = 0; i < n; i++){
        cin >> names[i];
    }

    vector<vector<i64>> G(26);
    auto find_edge = [](const string &s, const string &t){
        for (i64 i = 0; i < min(s.size(), t.size()); i++){
            if (s[i] != t[i]) return pair<i64, i64>(s[i] - 'a', t[i] - 'a');
        }
        return pair<i64, i64>(-1, -1);
    };
    for (i64 i = 0; i + 1 < n; i++){
        pair<i64, i64> e = find_edge(names[i], names[i + 1]);
        if (e != pair<i64, i64>(-1, -1)){
            G[e.first].emplace_back(e.second);
        } else if (e == pair<i64, i64>(-1, -1) && names[i].size() > names[i + 1].size()){
            // one is a prefix of the other
            // but the prefix is interpreted as larger
            cout << "Impossible" << endl;
            return;
        }
    }
    vector<i64> order = Graph::toposort(G);
    if (order.size() == 0){
        cout << "Impossible" << endl;
    } else {
        char ans[27];
        for (i64 i = 0; i < 26; i++){
            ans[order[i]] = (char)('a' + i);
        }
        ans[26] = '\0';
        cout << ans << endl;
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
