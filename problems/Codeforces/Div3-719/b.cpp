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

i64 build(i64 base, i64 len){
	i64 ans = 0;
	i64 pow10 = 1;
	for (i64 i = 0; i < len; i++){
		ans += base * pow10;
		pow10 *= 10;
	}
	return ans;
}

void solve(){
	i64 n, n_orig;
	cin >> n;
	n_orig = n;
	i64 len = 1;
	while (n >= 10){
		n /= 10;
		len++;
	}

	i64 estimate = build(n, len);
	cout << 9 * (len - 1) + n - 1 + ((estimate <= n_orig) ? 1 : 0) << endl;
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