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
