#define TESTCASES
// #define DEBUG
 
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

void solve(){
	i64 n, k;
	cin >> n >> k;
	vector<i64> a(n);

	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	// two ptrs
	i64 sunk = 0;
	i64 l = 0, r = n - 1;
	// try to sink a[l]
	while (k > 0 && l <= r){
		// attack left
		i64 dl = min((k + 1) / 2, a[l]);
	        i64 max_dr = min(k / 2, dl);
		a[l] -= dl;
		if (a[l] == 0){
			++l;
			++sunk;
			if (l > r){
				cout << n << endl;
				return;
			}
		}
		i64 comp = 0;
		while (comp < max_dr){
			i64 dr = min(max_dr - comp, a[r]); 
			a[r] -= dr;
			if (a[r] == 0){
				--r;
				++sunk;
				if (r < l){
					cout << n << endl;
					return;
				}
			}
			comp += dr;
		}
		k -= dl + max_dr;
	}
	cout << sunk << endl;
}
 
signed main(){
	fastio;
// #ifdef DEBUG
// 	freopen("/tmp/in", "r", stdin);
// #endif
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
