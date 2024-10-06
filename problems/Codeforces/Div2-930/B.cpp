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

const i64 INF = 2e18;

void solve(){
	i64 n;
	cin >> n;
	vector<vector<i64>> a(2, vector<i64>(n)), next(2, vector<i64>(n, -INF)), cnt(2, vector<i64>(n));

	char c;
	for (i64 i = 0; i < 2; i++){
		for (i64 j = 0; j < n; j++){
			cin >> c;
			if (c == '0') a[i][j] = 0;
			else a[i][j] = 1;
		}
		cin.ignore();
		// cin >> c; // read newline
	}

	// go by diagonals
	// dp[0][n - k] or dp[1][n - k - 1]
	next[1][n - 1] = 0;
	cnt[1][n - 1] = 1;
	next[0][n - 1] = -1;
	cnt[0][n - 1] = 1;
	next[1][n - 2] = 1;
	cnt[1][n - 2] = 1;

	for (i64 k = 2; k <= n - 1; k++){
		// up: dp[0][n - k]
		i64 ok = min(a[0][n - k + 1], a[1][n - k]);
		if (a[0][n - k + 1] == ok){
			next[0][n - k] = max(next[0][n - k], (i64)1);
			cnt[0][n - k] += cnt[0][n - k + 1];
		}
		if (a[1][n - k] == ok){
			next[0][n - k] = max(next[0][n - k], (i64)(-1));
			cnt[0][n - k] += cnt[1][n - k];
		}

		// down: dp[1][n - k - 1]
		// only one option: right
		next[1][n - k - 1] = 1;
		cnt[1][n - k - 1] += cnt[1][n - k];
	}

	i64 ok = min(a[0][1], a[1][0]);
	if (a[0][1] == ok){
		next[0][0] = max(next[0][0], (i64)1);
		cnt[0][0] += cnt[0][1];
	}
	if (a[1][0] == ok){
		next[0][0] = max(next[0][0], (i64)(-1));
		cnt[0][0] += cnt[1][0];
	}

	// FIXME: remove
	cout << "cnt=" << endl;
	for (i64 i = 0; i < 2; i++){
		for (i64 j = 0; j < n; j++){
			cout << cnt[i][j];
		}
		cout << endl;
	}
	return;

	// build path
	pair<i64, i64> p = make_pair(0, 0);
	string s = to_string(a[0][0]);
	while (next[p.first][p.second] != 0){
		if (next[p.first][p.second] == -1){
			++p.first;
		} else if (next[p.first][p.second] == 1){
			++p.second;
		}
		s += to_string(a[p.first][p.second]);
	}
	cout << s << endl;
	cout << cnt[0][0] << endl;
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
