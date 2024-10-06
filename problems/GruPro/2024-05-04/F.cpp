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

/*
let c_x = | {(i, j) : i * j <= x } |
= sum(i=1..N) min(floor(x / i), m)

we want the first x such that c_x >= k
we can calculate c_x in O(N) and search for x with binary search
*/

i64 n, m, k;

i64 c(i64 x){
	i64 ans = 0;
	for (i64 i = 1; i <= n; i++){
		ans += min(m, x / i);
	}
	return ans;
}

void solve(){
	cin >> n >> m >> k;
	i64 l = 1, r = n * m, ans = 1;
	while (l <= r){
		i64 mid = l + (r - l) / 2;
		if (c(mid) >= k){
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	cout << ans << endl;
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
