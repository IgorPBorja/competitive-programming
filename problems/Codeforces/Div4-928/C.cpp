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

i64 build(i64 rdigits[], i64 len){
	i64 cur_pow = 1;
	i64 x = 0;
	for (int i = 0; i < len; i++){
		x += rdigits[i] * cur_pow;
		cur_pow *= (i64)10;
	}
	return x;
}

void solve(){
	/*
	 * we have the recursion
	 * f(10^n - 1) = (0 + 1 + 2 + 3 + 4 + ... + 9)*10^{n - 1} + 10 * f(10^{n - 1} - 1)
	 * 
	 * For more general numbers
	 * f([a1]) = 1 + ... + a1
	 * f([a1a2]) = 1 + ... + [a1 0] + [a1 1] + ... + [a1 a2] = f([a1 0] - 1) + a1 * (a2 + 1) + f(a2)
	 * f([a1a2a3]) = f([a1 00] - 1) + [a1 00] + ... + [a1a2a3] = f([a1 00] - 1) + a1 * ([a2a3] + 1) + f([a2a3])
	 * In general if x = a1...an
	 * f(x) = f(a1 * 10^{n - 1} - 1) + a1 * ([a2...an] + 1) + f([a2...an])
	 *
	 * And of course 
	 * f(a1 * 10^n - 1) = (1 + ... + a1) * 10^{n - 1} + a1 * f(10^{n - 1} - 1)
	 */
	i64 n;
	cin >> n;

	i64 rdigits[10];

	// found ilog & stuff
	i64 len = 0, cur_pow = 1;
	while (n >= 1){
		// add to tail
		rdigits[len] = (n % 10);

		// update pow
		cur_pow *= 10;

		n /= 10;
		++len;
	}

	i64 dp_pow10[10], dp_suffix[10];
	// dp_pow10[i] = f(10^i - 1)
	// dp_suffix[i] = f(ai...a1a0)
	dp_pow10[0] = 0; // f(1)
	dp_suffix[0] = ( rdigits[0] * (rdigits[0] + 1) ) / 2;
	cur_pow = 1; // 10^{n - 1}
	for (int i = 1; i < len; i++){
		// f(10^i - 1) = (0 + 1 + 2 + 3 + 4 + ... + 9)*10^{i - 1} + 10 * f(10^{i - 1} - 1)
		dp_pow10[i] = (i64)45 * cur_pow + (i64)10 * dp_pow10[i - 1];
		
		// f(x) = f(a1 * 10^{n - 1} - 1) + a1 * ([a2...an] + 1) + f([a2...an])
		// f(ai * 10^i - 1) = (1 + ... + ai-1) * 10^i + ai * f(10^i - 1)

		cur_pow *= (i64)10;
		i64 f_lead = (  rdigits[i] * (rdigits[i] - 1)  / 2) * cur_pow;
		f_lead += rdigits[i] * dp_pow10[i];

		dp_suffix[i] = f_lead + rdigits[i] * (build(rdigits, i) + 1) + dp_suffix[i - 1];
	}
	cout << dp_suffix[len - 1] << endl;
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

