#define TESTCASES
 
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

/*
	
*/
struct DSU {
	vector<int> p, _size;

	void _init(int n){
		p.resize(n);
		_size.assign(n, 1);
		for (int i = 0; i < n; i++){
			p[i] = i;
		}
	}
	
	int get(int x){
		// with path compression
		if (p[x] == -1){
			return x;
		} else {
			p[x] = get(p[x]); // compress
			return p[x];
		} 
	}

	int size(int x){
		return _size[get(x)];
	}

	void merge(int x, int y){
		// small to large merge
		if (size(x) > size(y)){
			merge(y, x);
		}
		int px = get(x), py = get(y);
		p[x] = py;
		_size[py] += _size[px];
	}
}

void solve(){

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
