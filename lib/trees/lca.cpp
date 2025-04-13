#include <bits/stdc++.h>
using namespace std;

const int N = 2e5, LOGN = 20;
int lift[LOGN + 1][N];

void binary_lifting(const vector<vector<int>> &forest){
	const int n = forest.size();
	vector<int> parent(n, -1);
	for (int u = 0; u < n; u++){
		for (int v: forest[u]){
			parent[v] = u;
		}
	}
	for (int u = 0; u < n; u++){
		lift[0][u] = parent[u];
	}
	for (int k = 1; k <= LOGN; k++){
		for (int u = 0; u < n; u++){
			lift[k][u] = lift[k - 1][lift[k - 1][u]];
		}
	}
}

int jump(int u, int k){
	for (int i = 0; i <= LOGN; i++){
		if ((k >> i) & 1){
			u = lift[i][u];
		}
	}
	return u;
}

int LCA(
	int u, int v, const vector<int> &level,
	const vector<int> &parent
){
	// invariant: level[u] <= level[v]
	if (level[v] < level[u]) swap(u, v);
	v = jump(v, level[v] - level[u]);

	if (u == v){
		return u;
	}

	// loop invariant: u and v are distinct
	// (we have not reached a common ancestor yet)
	for (int i = LOGN; i >= 0; i--){
		if (lift[i][u] != lift[i][v]){
			// keeps loop invariant -> greedily take it!
			u = lift[i][u];
			v = lift[i][v];
		}
	}

	// at the end of the invariant we must be just one level below the LCA
	// otherwise we could have jumped more
	return parent[u];
}
