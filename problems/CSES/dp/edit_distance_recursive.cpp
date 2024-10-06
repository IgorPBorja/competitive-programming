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

const i64 INF = 2e18;

i64 edit_dist(i64 i, i64 j, vector<vector<i64>> &dp, string &s, string &t){
    // first case is replace, second is prepend, third is remove
    // dp[i][j] = min(mismatch + dp[i + 1][j + 1], 1 + dp[i][j + 1], 1 + dp[i + 1][j])
    if (i == s.size() && j == t.size()){
        return 0;
    } else if (i == s.size()){
        // can only remove from t now
        return (t.size() - j);
    } else if (j == t.size()){
        // can only remove from s now
        return (s.size() - i);
    } else if (dp[i][j] != -1){
        return dp[i][j];
    } else {
        i64 replace = ((s[i] == t[j]) ? 0 : 1) + edit_dist(i + 1, j + 1, dp, s, t);
        i64 add = 1 + edit_dist(i, j + 1, dp, s, t);
        i64 rm = 1 + edit_dist(i + 1, j, dp, s, t);
        dp[i][j] = min(replace, min(add, min(rm, INF)));
        return dp[i][j];
    }
}

void solve(){
    string s, t;
    cin >> s >> t;

    const i64 n = s.size(), m = t.size();
    vector<vector<i64>> dp(n, vector<i64>(m, -1));
    cout << edit_dist(0, 0, dp, s, t) << endl;
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
