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

i64 upsum(vector<i64> &b, i64 x){
	const i64 n = b.size();
	i64 ans = 0;
	for (i64 i = 0; i < n; i++){
		ans += max(x - b[i], (i64)0);
	}
	return ans;
}

// count of x, min_x, sum
tuple<i64, i64, i64> bsearch(vector<i64> &b, i64 k){
	i64 l = 1, r = 2e12 + 10, ans = 1;
	while (l <= r){
		i64 m = l + (r - l) / 2;
		i64 s = upsum(b, m);
		if (s <= k){
			ans = m;
			l = m + 1;
		} else {
			r = m - 1;
		}
	}

	i64 s = upsum(b, ans);
	i64 cnt_x = upsum(b, ans + 1) - s;
	return {cnt_x, ans, s};
	// return 
}

void solve(){
	i64 n, k;
	cin >> n >> k;

	vector<i64> a(n);
	
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}
	sort(a.begin(), a.end());

	auto[cnt_min, min_value, s] = bsearch(a, k);

	// x cnt can be brought down by a k - s factor
	i64 cnt_non_min = n - (cnt_min - (k - s));
	cout << (min_value - 1) * n + cnt_non_min + 1 << endl;
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
