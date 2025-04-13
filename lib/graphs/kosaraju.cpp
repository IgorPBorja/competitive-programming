#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> transpose(const vector<vector<int>> &g){
	vector<vector<int>> gt(g.size());
	for (int u = 0; u < g.size(); u++){
		for (int v: g[u]){
			gt[v].emplace_back(u);
		}
	}
	return gt;
}

void forward_dfs(
	const int u, const vector<vector<int>> &g, vector<bool> &vis, vector<int> &stack
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
	const int u, const vector<vector<int>> &g, vector<bool> &vis,
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

pair<vector<int>, int> scc(const vector<vector<int>> &g, int n){
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
