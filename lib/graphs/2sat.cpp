#include <bits/stdc++.h>
using namespace std;


namespace SAT2 {
    vector<vector<int>> build_graph(const vector<pair<int, int>> &clauses, int n){
        vector<vector<int>> g(2 * n);
        for (auto[x, y]: clauses){
            // (x or y) clause = (~x => y) clause and (~y => x) clause
            g[(x + n) % (2 * n)].emplace_back(y);
            g[(y + n) % (2 * n)].emplace_back(x);
        }
        return g;
    }
    vector<vector<int>> transpose(vector<vector<int>> &g){
        vector<vector<int>> gt(g.size());
        for (int u = 0; u < g.size(); u++){
            for (int v: g[u]){
                gt[v].emplace_back(u);
            }
        }
        return gt;
    }

    void forward_dfs(
		const int u, vector<vector<int>> &g, vector<bool> &vis, vector<int> &stack
	){
        vis[u] = true;
        for (int v: g[u]){
            if (!vis[v]){
                forward_dfs(v, g, vis, stack);
            }
        }
        stack.emplace_back(u);
    }

    void backward_dfs(
		const int u, vector<vector<int>> &g, vector<bool> &vis,
		vector<int> &comp, int c = 0
	){
        vis[u] = true;
        comp[u] = c;
        for (int v: g[u]){
            if (!vis[v]){
                backward_dfs(v, g, vis, comp, c);
            }
        }
    }

    pair<vector<int>, int> scc(const vector<pair<int, int>> &clauses, int n){
        vector<vector<int>> g = build_graph(clauses, n);
        vector<vector<int>> gt = transpose(g);

        const int s = g.size();
        vector<int> stack, comp(s);
        vector<bool> vis(s, false);
        for (int u = 0; u < s; u++){
            if (!vis[u]){
                forward_dfs(u, g, vis, stack);
            }
        }
        reverse(stack.begin(), stack.end());
        fill(vis.begin(), vis.end(), false);
        int c = 0;
        for (int u: stack){
            if (!vis[u]){
                backward_dfs(u, gt, vis, comp, c);
                ++c;
            }
        }
        return {comp, c};
    }

    pair<vector<bool>, bool> solve(const vector<pair<int, int>>& clauses, int n){
        // run scc (Kosaraju)
        auto[comp, num_comps] = scc(clauses, n);

        // build quotient graph
        vector<vector<int>> g_scc(num_comps);
        for (auto[x, y]: clauses){
            // (x or y) = (~x => y) = (~y => x)
            g_scc[comp[(x + n) % (2 * n)]].emplace_back(comp[y]);
            g_scc[comp[(y + n) % (2 * n)]].emplace_back(comp[x]);
        }

        // build valuation: mark as true the first one that appears
        vector<bool> valuation(n);
        for (int u = 0; u < n; u++){
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
