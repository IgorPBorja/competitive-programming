#include <bits/stdc++.h>
using namespace std;

vector<int> BIT(const vector<int> &a){
	int n = a.size();
	vector<int> B(n + 1, 0);

	for (int i = 0; i < n; i++){
		update(B, i, a[i]);  // sum a[i] to position i+1 of the BIT
	}
	return B;
}

int get(const vector<int> &BIT, int i){
	int s = 0;
	while (i >= 0){
		s += BIT[i];
		// i & -i == 2^lsb(i)
		i = i ^ (i & (-i));
	}
	return s;
}

void update(vector<int> &BIT, int i, int x){
	const int n = BIT.size() - 1;
	while (i <= n){
		BIT[i] += x;
		i += i & (-i);
	}
}