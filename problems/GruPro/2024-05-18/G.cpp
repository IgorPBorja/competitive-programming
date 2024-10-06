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

/*
suppose WLOG x[i] sorted (since we want the sum for all x[i] the order of processing does not matter)
for s = x[i] we have segments
	[x[0], x[i]]
	...
	[x[i], x[i]]
	[x[i], x[i + 1]]
	...
	[x[i], x[n-1]]

so if p <= x[i] we want i - lower_bound(p, x) + 1
and if p > x[i] we want n - 1 - lower_bound(p, x) + 1 = n - lower_bound(p, x)


so for p=1...x[1] we have i - 1 + 1 = i  ==> 
for p
*/

void solve(){
	i64 n;
	cin >> n;

	i64 x[n], p[n];
	pair<i64, i64> order[n];
	for (i64 i = 0; i < n; i++){
		cin >> x[i];
		order[i] = make_pair(x[i], i);
	}
	sort(x, x + n);
	sort(order, order + n);

	p[0] = x[0];
	for (i64 i = 1; i < n; i++){
		p[i] = p[i - 1] + x[i];
	}

	i64 ans[n];
	for (i64 i = 0; i < n; i++){
		ans[order[i].second] = n + (2 * i + 2 - n) * x[i] + p[n - 1] - 2 * p[i];
	}
	for (i64 i = 0; i < n; i++){
		cout << ans[i] << " ";
	}
	cout << endl;
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
