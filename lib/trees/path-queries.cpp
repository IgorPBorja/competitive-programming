// Tested on CSES Distance Queries
// sum queries on paths. Values are on vertices

#include <bits/stdc++.h>
using namespace std;


const int N = 2e5, LOGN = 20;
int lift[LOGN + 1][N];
int sums[LOGN + 1][N];

void binary_lifting(const vector<int>& parent, const vector<int>& values){
	const int n = parent.size();
	for (int u = 0; u < n; u++){
		lift[0][u] = parent[u];
        sums[0][u] = values[u];
	}
	for (int k = 1; k <= LOGN; k++){
		for (int u = 0; u < n; u++){
			lift[k][u] = lift[k - 1][lift[k - 1][u]];
            // u..p^(2^{k - 1})(u) and then p^(2^{k - 1}+1)(u) to p^(2^k(u))
            sums[k][u] = sums[k - 1][u] + sums[k - 1][lift[k - 1][u]];
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

// v[u] + v[p[u]] + ... + v[p^{2^k - 1}(u)]
int query_sum(int u, int k){
    int s = 0;
	for (int i = 0; i <= LOGN; i++){
		if ((k >> i) & 1){
            s += sums[i][u];
			u = lift[i][u];
		}
	}
	return s;
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

int path_sum(int u, int v, const vector<int> &level, const vector<int> &parent){
    int lca = LCA(u, v, level, parent);

    int left = query_sum(u, level[u] - level[lca]), right = query_sum(v, level[v] - level[lca]);
    return left + right + sums[0][lca];
}
