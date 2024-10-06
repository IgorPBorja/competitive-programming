#define TESTCASES
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

namespace SAT2 {
    vector<vector<i64>> build_graph(const vector<pair<i64, i64>> &clauses, i64 n){
        vector<vector<i64>> g(2 * n);
        for (auto[x, y]: clauses){
            // (x or y) clause = (~x => y) clause and (~y => x) clause
            g[(x + n) % (2 * n)].emplace_back(y);
            g[(y + n) % (2 * n)].emplace_back(x);
        }
        return g;
    }
    vector<vector<i64>> transpose(vector<vector<i64>> &g){
        vector<vector<i64>> gt(g.size());
        for (i64 u = 0; u < g.size(); u++){
            for (i64 v: g[u]){
                gt[v].emplace_back(u);
            }
        }
        return gt;
    }

    void forward_dfs(const i64 u, vector<vector<i64>> &g, vector<bool> &vis, vector<i64> &stack){
        vis[u] = true;
        for (i64 v: g[u]){
            if (!vis[v]){
                forward_dfs(v, g, vis, stack);
            }
        }
        stack.emplace_back(u);
    }

    void backward_dfs(const i64 u, vector<vector<i64>> &g, vector<bool> &vis, vector<i64> &comp, i64 c = 0){
        vis[u] = true;
        comp[u] = c;
        for (i64 v: g[u]){
            if (!vis[v]){
                backward_dfs(v, g, vis, comp, c);
            }
        }
    }

    pair<vector<i64>, i64> scc(const vector<pair<i64, i64>> &clauses, i64 n){
        vector<vector<i64>> g = build_graph(clauses, n);
        vector<vector<i64>> gt = transpose(g);

        const i64 s = g.size();
        vector<i64> stack, comp(s);
        vector<bool> vis(s, false);
        for (i64 u = 0; u < s; u++){
            if (!vis[u]){
                forward_dfs(u, g, vis, stack);
            }
        }
        reverse(stack.begin(), stack.end());
        fill(vis.begin(), vis.end(), false);
        i64 c = 0;
        for (i64 u: stack){
            if (!vis[u]){
                backward_dfs(u, gt, vis, comp, c);
                ++c;
            }
        }
        return {comp, c};
    }

    pair<vector<bool>, bool> solve(const vector<pair<i64, i64>>& clauses, i64 n){
        // run scc (Kosaraju)
        auto[comp, num_comps] = scc(clauses, n);

        // build quotient graph
        vector<vector<i64>> g_scc(num_comps);
        for (auto[x, y]: clauses){
            // (x or y) = (~x => y) = (~y => x)
            g_scc[comp[(x + n) % (2 * n)]].emplace_back(comp[y]);
            g_scc[comp[(y + n) % (2 * n)]].emplace_back(comp[x]);
        }

        // build valuation: mark as true the first one that appears
        vector<bool> valuation(n);
        for (i64 u = 0; u < n; u++){
            if (comp[u] < comp[u + n]){
                valuation[u] = false;
            } else {
                valuation[u] = true;
            }
        }

        // check valuation
        bool ok = true;
        for (auto[x, y]: clauses){
            bool left = ((x < n) ? valuation[x] : !valuation[x - n]);
            bool right = ((y < n) ? valuation[y] : !valuation[y - n]);
            ok &= left | right;
        }
        return {valuation, ok};
    }
};

void solve(){
	i64 n;
	cin >> n;

	i64 mat[3][n];
	for (i64 i = 0; i < 3; i++){
		for (i64 j = 0; j < n; j++){
			cin >> mat[i][j];
			if (mat[i][j] < 0) mat[i][j] = n - mat[i][j];
			--mat[i][j]; // 0-index
		}
	}


	// for each column a,b,c
	// we want to have at least two ones
	// so (a ^ b) v (b ^ c) v (c ^ a)
	// However, note that, using * for AND and + for OR
	// (a + b)*(b + c)*(c + a) = (a*b + b*c + c*a + b)*(c + a)
	// = (a*b*c + b*c + c*a + b*c + a*b + a*b*c + c*a + b*a) = (a*b*c + b*c + c*a + a*b)
	// = a*b + b*c + c*a
	// Total: 3 * n clauses
	vector<pair<i64, i64>> clauses(3 * n);
	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < 3; j++){
			clauses[3 * i + j] = {mat[j][i], mat[(j + 1) % 3][i]};
		}
	}

	auto[_, ok] = SAT2::solve(clauses, n);
	if (ok){
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
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
