#include <bits/stdc++.h>
using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2
bool has_cycle = false;

void dfs(vector<vector<int>> &g, int u, vector<int> &color){
	if (color[u] != WHITE){
		return;
	}
	color[u] = GRAY;
	for (int v: g[u]){
		if (color[v] == GRAY){
			has_cycle = true;
		} else if (color[v] == WHITE){
			dfs(g, u, color);
		}
	}
	color[u] = BLACK;
}