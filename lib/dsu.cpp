#include <bits/stdc++.h>
using namespace std;
 
struct DSU {
	vector<int> parent, sz;
	vector<vector<int>> elements;

	DSU(int n){
		parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
		sz.assign(n, 1);
		elements.resize(n);
		for (int i = 0; i < n; i++){
			elements[i].emplace_back(i);
		}
	}

	int find(int x){
		if (parent[x] != x){
			parent[x] = find(parent[x]);  // path-compression
		}
		return parent[x];
	}

	void unite(int x, int y){
		x = find(x);
		y = find(y);
		if (x == y){
			return;
		} else if (sz[x] > sz[y]) {
			swap(x, y);
		}
		sz[y] += sz[x];
		for (int z: elements[x]){
			elements[y].emplace_back(z);
		}
		parent[x] = y;
	}
};