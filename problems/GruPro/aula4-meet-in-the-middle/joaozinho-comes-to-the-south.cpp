// NOTE: PROBLEM LINK: https://judge.beecrowd.com/en/problems/view/3354 

// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
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

const i64 MOD = 1300031;

void solve(i64 n, i64 l, i64 r){
	vector<i64> a(n);

	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	i64 total = 0;
	for (i64 mask = 1; mask < (1ll << n); mask++){
		// lcm
		i64 lcm_val = 1;
		for (i64 i = 0; i < n; i++){
			if (mask & (1 << i)){
				lcm_val = lcm_val * (a[i] / __gcd(a[i], lcm_val));
			}
			if (lcm_val > 1e9){
				break;
			}
		}
		// cerr << "mask=" << mask << " lcm_val=" << lcm_val << endl;
		i64 sign = (__builtin_popcount(mask) % 2 == 1) ? 1 : -1;
		// multiples of lcm between i and f
		i64 left_bound = (l + lcm_val - 1) / lcm_val;  // will be 1 if lcm > 1e9
		i64 right_bound = r / lcm_val;  // will be zero
		// we want sum x * lcm from x = left_bound to x = right_bound
		// inclusive
		// ==> sum x * lcm from x = 0 to right_bound - left_bound + (right_bound - left_bound + 1) * left_bound * lcm
		i64 delta = (((right_bound - left_bound + 1) * (right_bound - left_bound)) / 2) % MOD;
		delta = (delta + (right_bound - left_bound + 1) * left_bound) % MOD;
		delta = (delta * lcm_val) % MOD;
		total = (total + (MOD + sign) * delta) % MOD;
	}
	cout << total << endl;
}
 
signed main(){
	fastio;
	while (true){
		i64 l, r, n;
		cin >> l >> r >> n;
		if (n == 0){
			break;
		}
		solve(n, l, r);
	}
}
