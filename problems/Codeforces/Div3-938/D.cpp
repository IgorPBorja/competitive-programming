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
	i64 n, m, k;
	i64 x;
	cin >> n >> m >> k;
	i64 a[n];
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	map<i64, i64> cnt_b;
	for (i64 i = 0; i < m; i++){
		cin >> x;
		++cnt_b[x];
	}

	// initial match
	i64 matches = 0;
	map<i64, i64> cnt_a;
	for (i64 i = 0; i < m; i++){
		++cnt_a[a[i]];
		if (cnt_a[a[i]] <= cnt_b[a[i]]){
			++matches;
		}
	}
	i64 ans = (matches >= k) ? 1 : 0;
	for (i64 i = m; i < n; i++){
		// remove a[i - m]
		--cnt_a[a[i - m]]; // >= 0
		if (cnt_a[a[i - m]] < cnt_b[a[i - m]]){
			--matches;
		}
		++cnt_a[a[i]];
		if (cnt_a[a[i]] <= cnt_b[a[i]]){
			++matches;
		}
		ans += (matches >= k) ? 1 : 0;
	}
	cout << ans << endl;
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