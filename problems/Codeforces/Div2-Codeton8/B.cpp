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

void solve(){
	
	i64 n;
	cin >> n;
	i64 a[n], p[n];
	i64 curr_mex = 0;

	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	for (i64 i = 0; i < n; i++){
		if (a[i] >= 0){
			// improve MEX!
			// p[i] = mex[i - 1]
			// mex[i] = a[i] + p[i]
			p[i] = curr_mex;
			curr_mex = a[i] + p[i];
		} else {
			// break mex
			// p[i] = mex[i] - a[i] = mex[i - 1] - a[i]
			p[i] = curr_mex - a[i];
		}
	}
	for (i64 i = 0; i < n; i++){
		cout << p[i] << " ";
	}
	cout << endl;
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
