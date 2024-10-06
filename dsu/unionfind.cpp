// #define TESTCASES
 
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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

struct DSU {
	int n;
	vector<int> parent;
	vector<int> sizes;

	void init(vector<int> data){
		// maps data to [1...n] according to indexes
		this->n = data.size();
		for (int i = 0; i < n; i++){
			this->parent.eb(i);
			this->sizes.eb(i);
		}
	}

	void init(int n){
		// maps data to [1...n] according to indexes
		this->n = n;
		for (int i = 0; i < n; i++){
			this->parent.eb(i);
			this->sizes.eb(i);
		}
	}

	// with path compression 
	int get(int a){
		if (this->parent[a] == a){
			return a;
		} else {
			this->parent[a] = get(this->parent[a]); // update path up and get root
			return this->parent[a];
		}
	}

	// with small-to-large heuristic
	void merge(int a, int b){
		if (this->sizes[a] > this->sizes[b]){
			merge(b, a);	
		}

		int root_a = this->get(a);
		int root_b = this->get(b);
		// join the small to the large 
		this->parent[root_a] = root_b;
		// update sizes
		this->sizes[b] += this->sizes[a];
	}
};

void solve(){
	int n, q;
	cin >> n >> q;
	DSU D;
	D.init(n);

	int t, u, v;
	for (int i = 0; i < q; i++){
		cin >> t >> u >> v;
		if (t == 0){
			// merge query
			D.merge(u, v);
		} else {
			// connection check query
			cout << ((D.get(u) == D.get(v)) ? 1 : 0) << endl;
		}
	}
}
 
signed main(){
	fastio;
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
