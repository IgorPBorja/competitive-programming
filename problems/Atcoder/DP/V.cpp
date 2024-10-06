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

constexpr i64 MAX_N = 2e5 + 10;

vector<i64> dp_subtree(MAX_N, -1);
vector<i64> dp_ascending(MAX_N, -1);
vector<vector<i64>> dfs_tree(MAX_N);
vector<vector<i64>> pref(MAX_N), suf(MAX_N);

void dfs(i64 u, i64 mod, const vector<vector<i64>> &tree, i64 p = -1){
    // dp subtree
    dp_subtree[u] = 1;

    for (i64 v: tree[u]){
        if (v != p){
            dfs_tree[u].emplace_back(v);
            dfs(v, mod, tree, u);
            dp_subtree[u] = (dp_subtree[u] * (dp_subtree[v] + 1)) % mod;
        }
    }
}

void mount_prods(i64 mod){
    for (i64 u = 0; u < MAX_N; u++){
        sort(dfs_tree[u].begin(), dfs_tree[u].end());
        const i64 deg = dfs_tree[u].size();

        pref[u].resize(deg + 1);
        suf[u].resize(deg + 1);
        pref[u][0] = 1;
        suf[u][deg] = 1;
        for (i64 i = 0; i < deg; i++){
            pref[u][i + 1] = (pref[u][i] * (1 + dp_subtree[dfs_tree[u][i]])) % mod;
            suf[u][deg - 1 - i] = (suf[u][deg - i] * (1 + dp_subtree[dfs_tree[u][deg - 1 - i]])) % mod;
        }
    }
}

void dfs2(i64 u, i64 mod, const vector<vector<i64>> &tree, i64 p = -1){
    if (p == -1) {
        dp_ascending[u] = 1;
    } else {
        dp_ascending[u] = dp_ascending[p];
        // we need prod(1 + dp_subtree[v]) where v != parent[p] and v != u
        // so we consider the dag/dfs tree and do suffix products on dp_subtree of the children
        // from 0 to deg - 1 (deg >= 1)
        i64 pos_child = lower_bound(dfs_tree[p].begin(), dfs_tree[p].end(), u) - dfs_tree[p].begin();
        dp_ascending[u] = (dp_ascending[u] * pref[p][pos_child]) % mod;
        dp_ascending[u] = (dp_ascending[u] * suf[p][pos_child + 1]) % mod;
        dp_ascending[u] = (dp_ascending[u] + 1) % mod;
    }
    for (i64 v: tree[u]){
        if (v != p){
            dfs2(v, mod, tree, u);
        }
    }
}

void solve(){
    i64 n, mod;
    cin >> n >> mod;
    vector<vector<i64>> tree(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        tree[a].emplace_back(b);
        tree[b].emplace_back(a);
    }

    dfs(0, mod, tree);
    mount_prods(mod);
    dfs2(0, mod, tree);

    // printgraph("dfs_tree=", dfs_tree);
    // printgraph("pref=", pref);
    // printgraph("suf=", suf);
    // printmsg("dp subtree=", dp_subtree.begin(), dp_subtree.end());
    // printmsg("dp ascending=", dp_ascending.begin(), dp_ascending.end());

    for (i64 i = 0; i < n; i++){
        cout << (dp_subtree[i] * dp_ascending[i]) % mod << endl;
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
