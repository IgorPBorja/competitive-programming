#include <bits/stdc++.h>
using namespace std;
 
const int INF = (int)2e9;  // might change depending on the problem

vector<vector<int>> floydWarshall(const vector<tuple<int, int, int>>& edges, int n){
	vector<vector<int>> d(n, vector<int>(n, INF));
	for (int i = 0; i < n; i++){
		d[i][i] = 0;
	}
	for (auto[a, b, w]: edges){
		d[a][b] = min(d[a][b], w);
	}
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (d[i][k] < INF && d[k][j] < INF)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
			}
		}
	}
	return d;
}