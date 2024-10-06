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
	i64 n, k;
	cin >> n >> k;

	i64 a[n];

	// finding inital k is all that matters
	i64 cur = 0;
	for (i64 i = 0; i < k / 2; i++){
		i64 runs = (n / k);
		if (2 * i + 1 <= (n % k)) ++runs; // is a part of incomplete run
		a[2 * i] = cur + runs;
		cur += runs;

		runs = (n / k);
		if (2 * i + 2 <= (n % k)) ++runs;
		a[2 * i + 1] = cur + 1;
		cur += runs;
	}

	i64 offset = -1;
	for (i64 i = k; i < n; i++){
		a[i] = a[i - k] + offset;
		offset = -offset;
	}
	
	for (i64 i = 0; i < n; i++) cout << a[i] << " ";
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
