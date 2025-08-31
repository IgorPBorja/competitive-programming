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

// toposort with bfs, returns the lexicographically smallest topological order
// Runs in O(n log n) because of sorting. Remove the sort to get a O(n) toposort
// Returns boolean indicating if topo order exists, and the order in case it does
pair<bool, vector<i64>> lexicographical_toposort(const vector<vector<i64>>& dag){
    const i64 n = dag.size();
    // dependencies_met[i]: how many j such that j->i
    // have received their order number
    vector<i64> dependencies_met(n, 0), in_degree(n, 0), order(n, -1);
    for (i64 u = 0; u < n; u++){
        for (i64 v: dag[u]){
            ++in_degree[v];
        }
    }

    priority_queue<i64, vector<i64>, greater<i64>> q;
    // min pq guarentees lexicographical order and topo order
    // by only pushing when all dependencies are met
    for (i64 u = 0; u < n; u++){
        if (!in_degree[u]) {
            q.emplace(u);
        }
    }
    i64 c = 0;
    while (!q.empty()){
        i64 u = q.top();
        order[u] = c++;
        q.pop();
        for (i64 v: dag[u]){
            ++dependencies_met[v];
            if (dependencies_met[v] == in_degree[v]){
                q.emplace(v);
            }
        }
    }
    for (i64 u = 0; u < n; u++){
        if (order[u] == -1) { // circular dependencies exist
            return {false, {}};
        }
    }
    return {true, order};
}

void solve(){
    i64 n, m;
    cin >> n >> m;
    vector<vector<i64>> dag(n);
    for (i64 i = 0; i < m; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        dag[u].emplace_back(v);
    }
    auto[ok, order] = lexicographical_toposort(dag);
    if (!ok){
        cout << -1 << endl;
    } else {
        for (i64 u = 0; u < n; u++){
            cout << order[u] + 1 << " ";
        }
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
