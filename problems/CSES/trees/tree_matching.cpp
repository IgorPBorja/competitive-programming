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

void dfs(i64 u, const vector<vector<i64>>& adj, vector<i64>& max_matching_no_root, vector<i64>& max_matching_root, i64 parent = -1){
    // init
    max_matching_no_root[u] = 0;
    max_matching_root[u] = 0;

    // descend
    for (i64 v: adj[u]){
        if (v == parent){
            continue;
        }
        dfs(v, adj, max_matching_no_root, max_matching_root, u);
    }

    // merge
    i64 sum_no_root = 0;
    for (i64 v: adj[u]){
        if (v == parent) continue;
        // can use child vertex v or not
        max_matching_no_root[u] += max(max_matching_no_root[v], max_matching_root[v]);
        sum_no_root += max_matching_no_root[v];
    }
    for (i64 v: adj[u]){
        if (v == parent) continue;
        // use edge (u, v) and then can't use v again
        // so it is the same as the maximum matching without u, just removing the
        // max(no_root[v], root[v]) and adding no_root[v] + 1
        max_matching_root[u] = max(
            max_matching_root[u],
            max_matching_no_root[u] - max(max_matching_no_root[v], max_matching_root[v]) + max_matching_no_root[v] + 1
        );
    }
}

void solve(){
    i64 n;
    cin >> n;

    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }

    // max_matching_no_root[u]: maximum matching on subtree rooted on u without using u
    // max_matching_root[u]: maximum matching on subtree rooted on u that does use u
    vector<i64> max_matching_no_root(n), max_matching_root(n);

    dfs(0, adj, max_matching_no_root, max_matching_root);
    cout << max(max_matching_no_root[0], max_matching_root[0]) << endl;
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
