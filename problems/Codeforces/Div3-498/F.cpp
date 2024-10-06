// #define TESTCASES
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
	i64 n, m, k;
	cin >> n >> m >> k;

	i64 a[n][m];
	map<i64, i64> l_paths[n][m], r_paths[n][m];

	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < m; j++){
			cin >> a[i][j];
		}
	}

	// will do n + m - 2 moves
	// complexity O(2 * max(n, m) * 2^(max(n, m)) ~ 4 * 10^7
	// will consider open interval in l (i.e not considering last xor)
	// and closed interval in r
	i64 l = (n + m - 2) / 2;
	i64 r = (n + m - 2) - l;

	for (i64 mask = 0; mask < (1ll << l); mask++){
		// 0 is right, 1 is down
		if (__builtin_popcount(mask) >= n || (l - __builtin_popcount(mask)) >= m){
			continue;
		}
		i64 i = 0, j = 0;
		i64 cur = 0;  // identity element for xor
		for (i64 idx = 0; idx < l; idx++){  
      			// late update -> desconsider last element in xor (OPEN)
			cur = cur ^ a[i][j];
			if (mask & (1ll << idx)){
				++i;
			} else {
				++j;
			}
		}
		++l_paths[i][j][cur];
	}
	for (i64 mask = 0; mask < (1ll << r); mask++){
		// 0 is left, 1 is up
		if (__builtin_popcount(mask) >= n || (r - __builtin_popcount(mask)) >= m){
			continue;
		}
		i64 i = n - 1, j = m - 1;
		i64 cur = a[n - 1][m - 1];
		for (i64 idx = 0; idx < r; idx++){
			if (mask & (1ll << idx)){
				--i;
			} else {
				--j;
			}
			cur = cur ^ a[i][j];
		}
		++r_paths[i][j][cur];
	}

	i64 total = 0;
	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < m; j++){
			for (auto[x, c]: l_paths[i][j]){
				i64 anti_xor = k ^ x;
				total += c * r_paths[i][j][anti_xor];
			}
		}
	}

	cout << total << endl;
}
 
signed main(){
	fastio;
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
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
