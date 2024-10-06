// NOTE: link: https://www.spoj.com/problems/NGM2/

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
	i64 n, k;
	cin >> n >> k;

	i64 a[k];
	for (i64 i = 0; i < k; i++){
		cin >> a[i];
	}

	i64 union_cnt = 0;
	for (i64 mask = 1; mask < (1ll << k); mask++){
		// calculate lcm
		i64 lcm = 1;
		for (i64 i = 0; i < k && lcm <= n; i++){
			if (mask & (1ll << i)){
				lcm = lcm * (a[i] / __gcd(lcm, a[i]));
			}
		}
		if (lcm > n){
			continue;
		}
		i64 sign = 2 * (__builtin_popcount(mask) % 2) - 1;
		union_cnt += sign * (n / lcm);
	}
	cout << n - union_cnt << endl;
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
