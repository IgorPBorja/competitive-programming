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

// each graph COMPONENT is either
// * a directed cycle
// * or multiple directed lines connecting to a directed cycle
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
    constexpr i64 WHITE = 0;
    constexpr i64 GRAY = 1;
    constexpr i64 BLACK = 2;
    constexpr i64 STACK_SIZE = 2e5 + 100;

    // performs iterative dfs to find first cycle of each component
    vector<vector<i64>> first_cycle_function_graph(const vector<i64> &f){
        const i64 n = f.size();
        vector<i64> colors(n, 0);
        vector<vector<i64>> cycles;

        // reserve some space so that insertion is O(1)
        vector<i64> stack;
        stack.reserve(STACK_SIZE);

        for (i64 src = 0; src < n; src++){
            if (colors[src] != WHITE) continue;
            stack.emplace_back(src);
            colors[src] = GRAY;
            while (!stack.empty()){
                i64 u = stack.back();
                i64 v = f[u];
                if (colors[v] == WHITE){
                    colors[v] = GRAY;
                    stack.emplace_back(v);
                    continue;
                } else if (colors[v] == GRAY){
                    // found cycle: save it! (and continue as if nothing happened)
                    cycles.emplace_back(vector<i64>());
                    for (i64 i = stack.size() - 1; i >= 0 && stack[i] != v; i--){
                        cycles.back().emplace_back(stack[i]);
                    }
                    cycles.back().emplace_back(v);
                } 
                colors[u] = BLACK;
                stack.pop_back();
            }
        }
        return cycles;
    }

    // binary search for first orbit position in a cycle
    pair<i64, i64> find_first_periodic_point(i64 u, const vector<bool> &in_cycle, const vector<vector<i64>> &f_lifted){
        i64 l = 0, r = f_lifted[0].size();
        i64 ans = r, periodic_point;
        while (l <= r){
            i64 m = l + (r - l) / 2;
            i64 vertex = BinaryLift::apply_compose(f_lifted, u, m);
            bool is_periodic = in_cycle[vertex];
            if (!is_periodic){
                l = m + 1;
            } else {
                ans = m;
                periodic_point = vertex;
                r = m - 1;
            }
        }
        return {ans, periodic_point};
    }
}

void solve(){
    i64 n;
    cin >> n;

    vector<i64> f(n);

    for (i64 i = 0; i < n; i++){
        i64 j;
        cin >> j;
        --j;
        f[i] = j;
    }

    vector<vector<i64>> cycles = CycleFinder::first_cycle_function_graph(f);
    vector<bool> in_cycle(n, false);
    vector<i64> cycle_sizes(n);
    for (const vector<i64>& c: cycles) {
        for (i64 x: c){
            in_cycle[x] = true;
            cycle_sizes[x] = c.size();
        }
    }
    vector<vector<i64>> f_lifted = BinaryLift::blift(f, n);

    for (i64 i = 0; i < n; i++){
        auto[k, p] = CycleFinder::find_first_periodic_point(i, in_cycle, f_lifted);
        cout << k + cycle_sizes[p] << " ";
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
