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

i64 backtrack(vector<i64> &a, i64 i, i64 idx, i64 k, i64 cur){
	if (idx == k){
		return cur;	
	} else {
		// choose j ==> a.size() - j options (counting this chosen), and we should have this >= k - 1 - idx + 1 = k - idx
		i64 ans = 0;
		for (i64 j = i + 1; a.size() - j >= k - idx; j++){
			ans = max(ans, backtrack(a, j, idx + 1, k, cur & a[j]));
		}
		return ans;
	}
}

void solve(){
	i64 n, k;
	cin >> n >> k;

	vector<i64> a(n);
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}
	i64 ans = backtrack(a, -1, 0, k, (1ll << 30) - 1ll);
	cout << ans << endl;
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
