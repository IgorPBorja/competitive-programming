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

vector<i64> prefix(const vector<i64>& a){
	vector<i64> p(a.size());
	p[0] = a[0];
	for (i64 i = 1; i < a.size(); i++) p[i] = a[i] + p[i - 1];
	return p;
}

void solve(){
	i64 n, m;
	cin >> n >> m;
	vector<i64> a(n), b(n), dp(n + 1);
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}
	for (i64 i = 0; i < n; i++){
		cin >> b[i];
	}

	vector<i64> prefix_b = prefix(b);

	dp[n] = prefix_b[n - 1];
	i64 suffix_min = dp[n];
	for (i64 i = n - 1; i >= 0; i--){
		dp[i] = a[i] - b[i] + suffix_min;
		suffix_min = min(suffix_min, dp[i]);
	}

	i64 min_m = dp[0];
	for (i64 i = 1; i < m; i++){
		min_m = min(min_m, dp[i] - prefix_b[i - 1]);
	}
	cout << min_m << endl;
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
