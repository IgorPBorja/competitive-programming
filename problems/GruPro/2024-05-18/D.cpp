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

	i64 a[n];
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	i64 s = 0;
	for (i64 j = 0; j < k; j++){
		s += a[j];
	}
	i64 best = s;
	i64 argidx = 0;
	// start at i
	for (i64 i = 1; i + k <= n; i++){
		// i-1 ... i + k - 2 ==> i ... i + k - 1
		s = s - a[i - 1] + a[i + k - 1];
		if (s < best){
			best = s;
			argidx = i;
		}
	}
	cout << argidx + 1 << endl; // 1-indexed
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
