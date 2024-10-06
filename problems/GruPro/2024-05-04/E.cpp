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

i64 isqrt(i64 x){
	i64 l = 1, r = x;
	i64 ans = 1;
	while (l <= r){
		i64 m = l + (r - l) / 2;
		if (m * m <= x){
			ans = m;
			l = m + 1;
		} else {
			r = m - 1;
		}
	}
	return ans;
}

void solve(){
	i64 n;
	cin >> n;

	// c = b + 1
	// c^2 - b^2 = a^2 ==> 2b + 1 = a^2
	// (also a^2 = b + c = 2b + 1)
	i64 r = isqrt(2 * n - 1);
	// odd nums <= r
	i64 cnt = (r - 1) / 2;
	cout << cnt << endl;
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

