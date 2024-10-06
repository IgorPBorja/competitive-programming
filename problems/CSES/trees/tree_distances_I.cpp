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

// f1(x) = max depth of subtree rooted at x
// f2(x) = second max depth of subtree rooted at x
// g(x) = max path from x going through the parent
// we have g(x) = 1 + max(f2(p[x]), g(p[x])) if x is in the max subtree of its parent, else 1 + max(f1(p[x]), g(p[x]))

const i64 MAXN = 2e5;
i64 parent[MAXN];
i64 max_depth[MAXN];
i64 optimal_child[MAXN];
i64 second_max_depth[MAXN];

void dfs(vector<vector<i64>> &tree, i64 u){
    max_depth[u] = 0;
    optimal_child[u] = -1;
    for (i64 v: tree[u]){
        if (v == parent[u]) continue;  // avoid trivial cycles
        dfs(tree, v);
        if (1 + max_depth[v] > max_depth[u]){
            second_max_depth[u] = max_depth[u];
            optimal_child[u] = v;
            max_depth[u] = 1 + max_depth[v];
        } else if (1 + max_depth[v] > second_max_depth[u]){
            second_max_depth[u] = 1 + max_depth[v];
        }
    }
}

void root_tree(vector<vector<i64>> &tree, i64 u, i64 p=-1){
    parent[u] = p;
    for (i64 v: tree[u]){
        if (v == p) continue;
        root_tree(tree, v, u);
    }
}

void solve(){
    i64 n;
    cin >> n;

    vector<vector<i64>> tree(n);
    i64 a, b;
    for (i64 i = 0; i < n - 1; i++){
        cin >> a >> b;
        --a; --b;
        tree[a].emplace_back(b);
        tree[b].emplace_back(a);
    }

    root_tree(tree, 0);
    dfs(tree, 0);

    i64 up_dist[n]; // down dist is just max depth of subtree
    // bfs
    queue<pair<i64, i64>> q;
    q.emplace(0, 0);
    while (!q.empty()){
        auto[d, u] = q.front();
        q.pop();
        up_dist[u] = d;
        for (i64 v: tree[u]){
            if (v == parent[u]) continue;
            else if (v == optimal_child[u]) q.emplace(1 + max(second_max_depth[u], up_dist[u]), v);
            else q.emplace(1 + max(max_depth[u], up_dist[u]), v);
        }
    }

    // printmsg("max d=", begin(max_depth), begin(max_depth) + n);
    // printmsg("second max d=", begin(second_max_depth), begin(second_max_depth) + n);
    // printmsg("up dist=", up_dist, up_dist + n);

    for (i64 i = 0; i < n; i++){
        cout << max(max_depth[i], up_dist[i]) << " ";
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
