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

/*
One must stay fixed

ans = min(i=0...n-1)
{
	sum(j=0...i-1)(p[i] - p[j] - i + j) + sum(j=i+1...n-1)(p[j] - p[i] + i - j)
	= i * (p[i] - i) - PREFIX(p - id)[...i-1]
		+ SUFFIX(p - id)[i + 1...] - (n - i - 1) * (p[i] - i) 
}
*/

void solve(){
	int s;
	char c;
	cin >> s;

	vector<i64> diff;
	for (i64 i = 0; i < s; i++){
		cin >> c;
		if (c == '*'){
			diff.eb(i - diff.size());
		}
	}
	i64 n = diff.size();
	i64 pref[n + 1], suf[n + 1];
	pref[0] = 0; suf[n] = 0;
	for (i64 i = 1; i <= n; i++){
		pref[i] = pref[i - 1] + diff[i - 1];
	}
	for (i64 i = n - 1; i >= 0; i--){
		suf[i] = suf[i + 1] + diff[i];
	}

	/*
	= i * (p[i] - i) - PREFIX(p - id)[...i-1]
		+ SUFFIX(p - id)[i + 1...] - (n - i - 1) * (p[i] - i)
	*/
	i64 ans = 2e18;
	for (i64 i = 0; i < n; i++){
		ans = min(ans,
			i * diff[i] - pref[i] + suf[i + 1] - (n - 1 - i) * diff[i]
		);
	}
	if (n == 0){
		cout << 0 << endl;
	} else {
		cout << ans << endl;
	}
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
