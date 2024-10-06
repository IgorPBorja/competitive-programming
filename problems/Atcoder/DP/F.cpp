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
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

void solve(){
    string s, t;
    cin >> s >> t;

    const i64 n = s.size(), m = t.size();

    // LCS ending before s[n] and t[m], considering 1-indexed positions
    vector<vector<i64>> dp(n + 1, vector<i64>(m + 1, 0));
    // last diff step made for this LCS
    vector<vector<pair<i64, i64>>> prev(n + 1, vector<pair<i64, i64>>(m + 1, make_pair(0,0)));

    for (i64 i = 0; i < n; i++){
        dp[i][0] = 0;
        prev[i][0] = {0,0};
    }
    for (i64 j = 0; j < m; j++){
        dp[0][j] = 0;
        prev[0][j] = {0,0};
    }

    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            i64 val = max(dp[i][j + 1], dp[i + 1][j]); // do not use either s[i] or t[j]
            if (s[i] == t[j]){
                val = max(val, dp[i][j] + 1);
            }
            if (s[i] == t[j] && val == dp[i][j] + 1){
                prev[i + 1][j + 1] = make_pair(-1, -1);
            } else if (val == dp[i][j + 1]){
                prev[i + 1][j + 1] = make_pair(-1, 0);
            } else if (val == dp[i + 1][j]){
                prev[i + 1][j + 1] = make_pair(0, -1);
            }
            dp[i + 1][j + 1] = val;
        }
    }

    string lcs;
    pair<i64, i64> cur = {n, m};
    while (prev[cur.first][cur.second] != make_pair((i64)0,(i64)0)){
        if (prev[cur.first][cur.second] == make_pair((i64)(-1), (i64)(-1))){
            // used char
            lcs.push_back(s[cur.first - 1]);
        }
        cur = make_pair(cur.first + prev[cur.first][cur.second].first, cur.second + prev[cur.first][cur.second].second);
    }
    reverse(lcs.begin(), lcs.end());
    cout << lcs << endl;
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
