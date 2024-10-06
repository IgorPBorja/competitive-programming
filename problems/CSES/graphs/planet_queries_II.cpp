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
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

// each graph COMPONENT is either
// * a directed cycle
// * a directed tree connecting to a directed cycle
// * or a single point

namespace BinaryLift {
    // O(log n) calculation of composition given precomputed binary lifting table
    i64 apply_compose(const vector<vector<i64>> &f_lifted, i64 x, i64 k){
        i64 b = f_lifted.size();
        for (i64 i = 0; i < b; i++){
            if (k & (1ll << i)){
                x = f_lifted[i][x];
            }
        }
        return x;
    }

    // O(n log n) precomputation of binary lifting table
    vector<vector<i64>> blift(const vector<i64> &f, i64 M){
        const i64 n = f.size();
        i64 ilog = 0;
        while ((1ll << (ilog + 1) <= M)) ++ilog;

        vector<vector<i64>> f_lifted(ilog + 1, vector<i64>(n));
        copy(f.begin(), f.end(), f_lifted[0].begin());
        for (i64 k = 1; k <= ilog; k++){
            for (i64 i = 0; i < n; i++){
                f_lifted[k][i] = f_lifted[k - 1][f_lifted[k - 1][i]];
            }
        }
        return f_lifted;
    }
}

namespace CycleFinder {
    constexpr i64 WHITE = 0, GRAY = 1, BLACK = 2;
    vector<i64> color;
    vector<bool> in_cycle;
    vector<vector<i64>> cycles;

    void toposort_dfs(i64 u, const vector<i64> &f, vector<i64> &path){
        color[u] = GRAY;
        path.emplace_back(u);
        if (f[u] == u){
            cycles.emplace_back(vector<i64>(1, u));
        }
        else if (f[u] != u && color[f[u]] == GRAY){
            // f[u] -> ... -> u -> f[u]
            vector<i64> cycle;
            for (i64 i = path.size() - 1; i >= 0 && path[i] != f[u]; i--){
                cycle.emplace_back(path[i]);
            }
            cycle.emplace_back(f[u]);
            reverse(cycle.begin(), cycle.end());
            // will backtrack up to f[u]
            cycles.emplace_back(cycle);
        } else if (color[f[u]] == WHITE){
            toposort_dfs(f[u], f, path);
        }
        color[u] = BLACK;
    }

    // performs iterative dfs to find first cycle of each component
    vector<vector<i64>> first_cycle_function_graph(const vector<i64> &f){
        const i64 n = f.size();
        color.assign(n, WHITE);
        in_cycle.assign(n, false);

        vector<i64> path;
        for (i64 x = 0; x < n; x++){
            if (color[x] == WHITE){
                // line-cycle components
                toposort_dfs(x, f, path);
            }
        }
        return cycles;
    }
}

// returns dist to cycle and modifies cycle num
pair<vector<i64>, vector<i64>> dist_to_cycle(
        const vector<i64> &f,
        const vector<bool> &in_cycle,
        vector<i64> cycle_num
){
    const i64 n = f.size();
    vector<vector<i64>> f_inv(n);
    vector<i64> dist_to_cycle(n, -1);

    for (i64 x = 0; x < n; x++){
        f_inv[f[x]].emplace_back(x);
    }
    queue<tuple<i64, i64, i64>> q;
    for (i64 x = 0; x < n; x++){
        if (in_cycle[x]) q.emplace(0, cycle_num[x], x);
    }
    while (!q.empty()){
        auto[d, c_idx, x] = q.front();
        q.pop();
        if (dist_to_cycle[x] != -1) continue;
        dist_to_cycle[x] = d;
        cycle_num[x] = c_idx;
        for (i64 y: f_inv[x]){
            if (dist_to_cycle[y] == -1){
                q.emplace(d + 1, c_idx, y);
            }
        }
    }
    return { dist_to_cycle, cycle_num };
}

pair<vector<i64>, vector<i64>> process_cycles(const vector<vector<i64>> &cycles, i64 n){
    // build cycle numbers
    // O(n)
    vector<i64> cycle_num(n);
    vector<i64> cycle_position(n);
    for (i64 i = 0; i < cycles.size(); i++){
        const vector<i64> c = cycles[i];
        for (i64 j = 0; j < c.size(); j++){
            cycle_num[c[j]] = i;
            cycle_position[c[j]] = j;
        }
    }
    return {cycle_num, cycle_position};
}

void solve(){
    i64 n, q;
    cin >> n >> q;

    vector<i64> f(n);

    for (i64 i = 0; i < n; i++){
        i64 j;
        cin >> j;
        --j;
        f[i] = j;
    }

    vector<vector<i64>> cycles = CycleFinder::first_cycle_function_graph(f);
    vector<bool> in_cycle(n, false);
    for (const vector<i64>& c: cycles) {
        for (i64 x: c){
            in_cycle[x] = true;
        }
    }

    auto[initial_cycle_num, cycle_position] = process_cycles(cycles, n);
    auto[dist, cycle_num] = dist_to_cycle(f, in_cycle, initial_cycle_num);
    vector<vector<i64>> f_lifted = BinaryLift::blift(f, n + 1);

    for (i64 i = 0; i < q; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        if (cycle_num[a] != cycle_num[b]){
            // cout << "case 1" << endl;
            // point to different cycles ==> different systems/components
            cout << -1 << endl;
        } else if ((in_cycle[a] && !in_cycle[b])){
            // cout << "case 2" << endl;
            // a is in a cycle and b is in a tree
            cout << -1 << endl;
        } else if (!in_cycle[a] && !in_cycle[b] && dist[a] < dist[b]){
            // cout << "case 3" << endl;
            // a and b are in tree but b comes before
            cout << -1 << endl;
        } else if ((!in_cycle[a] && !in_cycle[b])){
            // cout << "case 4" << endl;
            // in the same line, but b comes after
            i64 diff = dist[a] - dist[b];
            i64 c = BinaryLift::apply_compose(f_lifted, a, diff);
            if (c != b) {
                cout << -1 << endl;
            } else {
                cout << diff << endl;
            }
        } else if (in_cycle[a] && in_cycle[b]){
            // cout << "case 5" << endl;
            i64 cyc_size = cycles[cycle_num[a]].size();
            i64 cyc_delta = (cycle_position[b] - cycle_position[a] + cyc_size) % cyc_size;
            cout << cyc_delta << endl;
        } else if (!in_cycle[a] && in_cycle[b]){
            // cout << "case 6" << endl;
            i64 p = BinaryLift::apply_compose(f_lifted, a, dist[a]);
            i64 cyc_size = cycles[cycle_num[b]].size();
            i64 cyc_delta = (cycle_position[b] - cycle_position[p] + cyc_size) % cyc_size;
            cout << dist[a] + cyc_delta << endl;
        }
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
