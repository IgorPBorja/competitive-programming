// #define TESTCASES
// #define DEBUG
#pragma GCC optimize("O3")   // aggresive optim
#pragma GCC target("avx2")
 
#include <bits/stdc++.h>
using namespace std;
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

int _depth_counts[(int)2e5 + 1];  // global array
int blocked[(int)2e5 + 1];
int sz[(int)2e5 + 1];
int current_component_depth = 0;

int n, k;
i64 ans = 0;
vector<vector<int>> T;

void subtree_sizes(int u, int p = -1){
    sz[u] = 1;
    for (int v: T[u]){
        if (v == p || blocked[v]) continue;
        subtree_sizes(v, u);
        sz[u] += sz[v];
    }
}

int centroid(
    int u,
    int component_size,
    int p = -1
){
    for (int v: T[u]){
        if (v == p || blocked[v]) continue;
        if (sz[v] > component_size / 2) return centroid(v, component_size, u);
    }
    return u;
}

// count contributions on a subtree of u wrt to paths of size k passing through component root
// since it starts on child of component root, depth starts at 1
void count_contributions(int u, int k, int d = 1, int p = -1){
    if (d > k) return;  // d == k is ok since there is the path with 0 depth (just the centroid) to complement
    current_component_depth = max(current_component_depth, d);
    ans += _depth_counts[k - d];
    for (int v: T[u]){
        if (v == p || blocked[v]) continue;
        count_contributions(v, k, d + 1, u);
    }
}

void save_contributions(int u, int k, int d = 1, int p = -1){
    if (d > k) return;
    ++_depth_counts[d];
    for (int v: T[u]){
        if (v == p || blocked[v]) continue;
        save_contributions(v, k, d + 1, u);
    }
}

// recursive is easier to control 
void k_paths_decomp(int root, int k, int p = -1){
    subtree_sizes(root);
    int u = centroid(root, sz[root]);

    blocked[u] = true;
    current_component_depth = 0;
    _depth_counts[0] = 1;

    for (int v: T[u]){
        if (v == p) continue;
        if (blocked[v]) continue;
        count_contributions(v, k);
        save_contributions(v, k);
    }
    fill(_depth_counts, _depth_counts + current_component_depth + 1, (int)0);
    for (int v: T[u]){
        if (v == p || blocked[v]) continue;
        k_paths_decomp(v, k);
    }
}

void solve(){
    cin >> n >> k;
    T.resize(n);
    fill(blocked, blocked + n + 1, false);
    fill(_depth_counts, _depth_counts + n + 1, 0);
    for (int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        --a; --b;
        T[a].emplace_back(b);
        T[b].emplace_back(a);
    }
    k_paths_decomp(0, k);
    cout << ans << endl;
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
