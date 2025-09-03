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

struct MaximumMatchingFunctionalGraph {
    /*
    functional graphs contain chains: upside down trees rooted at vertices of a cycle
    We can solve maximum matching on those trees in O(|tree|) using dp
    with dp[v][0] = maximum matching on subtree rooted at v not using v
    and dp[v][1] = maximum matching on subtree rooted at v forcibly using v

    If we can use a cycle vertex to improve matching (i.e dp[u][1] > dp[u][0]) for some cycle vertex u, we should,
    since if this u would be matched to a vertex v in the cycle we can instead match it with someone on the
    subtree and get an equivalent number of matched pairs

    Therefore compute which cycle vertices would be used in order to breakdown the cycle, then break the cycle into segments
    if needed. Note that 
    maximum_matching(cycle of length k) = max
    */

    const vector<i64> f;
    vector<vector<i64>> rev_dag;
    vector<i64> dp[2], vis, in_path;
    vector<vector<i64>> cycles;
    vector<i64> in_cycle;
    i64 n;

    MaximumMatchingFunctionalGraph(const vector<i64> functional_dag) : f(functional_dag) , n(functional_dag.size()) {
        rev_dag.resize(n);
        for (i64 u = 0; u < n; u++){
            rev_dag[functional_dag[u]].emplace_back(u);
        }
        dp[0].assign(n, 0);
        dp[1].assign(n, 0);
        vis.assign(n, 0);
        in_path.assign(n, 0);
        in_cycle.assign(n, 0);

        for (i64 u = 0; u < n; u++){
            vector<i64> path;
            if (!vis[u]) dfs_build_cycles(u, path);
        }
    }

    i64 maximum_matching(){
        i64 global_max_matching = 0;
        for (const auto& cyc: cycles){
            global_max_matching += solve_cycle(cyc);
        }
        return global_max_matching;
    }

    void dfs_build_cycles(i64 u, vector<i64>& path){
        path.emplace_back(u);
        in_path[u] = true;
        vis[u] = true;
        if (!vis[f[u]]){
            dfs_build_cycles(f[u], path);
        } else if (in_path[f[u]]){  // closed cycle
            // find f[u] and go from f[u] to end of path
            // this is your cycle
            vector<i64> cyc;
            for (i64 i = path.size() - 1; i >= 0; i--){
                cyc.emplace_back(path[i]);
                in_cycle[path[i]] = true;
                if (path[i] == f[u]) { // took closing edge
                    break;
                }
            }
            cycles.push_back(cyc);
        }
        in_path[u] = false;
    }

    void _maximum_matching_on_subtree(i64 u){
        dp[0][u] = dp[1][u] = 0;
        i64 sum = 0;
        for (i64 v: rev_dag[u]){
            // avoid going into cycle if u is cycle node
            if (in_cycle[v]) continue;
            _maximum_matching_on_subtree(v);
            dp[0][u] += max(dp[0][v], dp[1][v]);
            sum += max(dp[0][v], dp[1][v]);
        }
        // now try to force use of edge uv
        for (i64 v: rev_dag[u]){
            if (in_cycle[v]) continue;
            dp[1][u] = max(dp[1][u], 1 + dp[0][v] + sum - max(dp[0][v], dp[1][v]));
        }
    }

    i64 solve_cycle(const vector<i64>& cyc){
        for (i64 cycle_node: cyc){
            _maximum_matching_on_subtree(cycle_node);
        }

        i64 max_matching = 0;
        vector<vector<i64>> segments;
        vector<i64> cur_segment;
        for (i64 u: cyc){
            if (dp[0][u] < dp[1][u]){  // best to use
                if (!cur_segment.empty()){
                    segments.emplace_back(cur_segment);
                    cur_segment.clear();
                }
            } else {
                cur_segment.emplace_back(u);
            }
            max_matching += max(dp[0][u], dp[1][u]);  // always >= dp[u][0] since can use u or not
        }
        if (!cur_segment.empty()){
            segments.emplace_back(cur_segment);
            cur_segment.clear();
        }
        vector<i64> len;
        i64 k = segments.size();
        for (i64 i = 0; i < k; i++){
            len.emplace_back(segments[i].size());
        }
        // NOTE: might be able to merge first segment with last!
        // since last segment might end up at last element and first segment
        // start at first element
        // For ex. dp vector over cycle might be (0 0 0 1 0), so merging we would have a segment of length 4
        // and answer = floor(4/2) + 1 = 3, while not merging answer = floor(3/2) + floor(1/2) + 1 = 2
        // concrete example: 1->2->3->4->5->1 and 6->2
        if (segments.size() >= 2 && segments[0][0] == cyc[0] && segments.back().back() == cyc.back()){
            // merge last with first because of cycle
            len[0] += len.back();
            len.pop_back();
        }
        for (i64 sz: len){
            // matching on line (possibly cycle)
            max_matching += sz / 2;
        }
        return max_matching;
    }
};

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

void solve(){
    i64 n;
    cin >> n;
    vector<i64> f(n);
    for (i64 i = 0; i < n; i++){
        // edge i -> f[i]
        cin >> f[i];
        --f[i];  // is 1-indexed
    }
    MaximumMatchingFunctionalGraph Gf(f);
    cout << Gf.maximum_matching() << endl;
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

