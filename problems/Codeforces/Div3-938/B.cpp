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

bool ok(map<i64, i64>& cnt, i64 a11, i64 c, i64 d, i64 n){
	vector<vector<i64>> a(n, vector<i64>(n));

	a[0][0] = a11;
	for (i64 j = 0; j + 1 < n; j++){
		if (cnt[a[0][j] + d] == 0){
			return false;
		} else {
			a[0][j + 1] = a[0][j] + d;
			--cnt[a[0][j] + d];
		}
	}
	for (i64 i = 1; i < n; i++){
		if (cnt[a[i - 1][0] + c] == 0){
			return false;
		} else {
			a[i][0] = a[i - 1][0] + c;
			--cnt[a[i - 1][0] + c];
			for (i64 j = 0; j + 1 < n; j++){
				if (cnt[a[i][j] + d] == 0){
					return false;
				} else {
					a[i][j + 1] = a[i][j] + d;
					--cnt[a[i][j] + d];
				}
			}
		}
	}
	return true;
}

void solve(){
	i64 n, c, d;
	cin >> n >> c >> d;
	map<i64, i64> cnt;
	i64 a11 = 2e18, x;
	for (i64 i = 0; i < n * n; i++){
		cin >> x;
		a11 = min(a11, x);
		++cnt[x];
	}
	if (ok(cnt, a11, c, d, n)){
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}
 
signed main(){
	fastio;
// #ifdef DEBUG
// 	freopen("/tmp/in", "r", stdin);
// #endif
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
