//#define TESTCASES
 
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
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

// FIXME
const i64 M = 1e6;
const i64 N = 1e6;
vector<i64> c[M + 1], k[N]; // O(M + n), O(N + sum k_i)
i64 sum_kinv[M + 1];
const i64 MOD = 998244353;


i64 bexp(i64 a, i64 exp){
	if (exp == 0){
		return 1;
	}
	i64 mid = bexp(a, exp / 2);

	if (exp % 2 == 0){
		return (mid * mid) % MOD;
	}
	else {
		return (((mid * mid) % MOD) * a) % MOD;
	}
}

i64 modinv(i64 x){
	return bexp(x, MOD - (i64)2) % MOD;
}

void solve(){
	i64 n, ki, val;
	cin >> n; // 1 <= n <= 1e6
	for (i64 i = 0; i < n; i++){
		cin >> ki;
		for (i64 j = 0; j < ki; j++){
			cin >> val; // 0 <= val <= 1e6
			k[i].eb(val); // kid i wants val
			c[val].eb(i); // val is wanted by kid i
		}
	}
	// calculate sum(x in c[y]) 1 / size(k[x])
	for (i64 y = 0; y <= M; y++){
		for (i64 x: c[y]){
			sum_kinv[y] = (sum_kinv[y] + modinv(k[x].size())) % MOD;
		}
	}

	i64 ans = 0;
	for (i64 y = 0; y <= M; y++){
		ans = (ans + (c[y].size() * sum_kinv[y]) % MOD) % MOD;
	}
	ans = (ans * modinv((n * n) % MOD)) % MOD;
	cout << ans << endl;
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
