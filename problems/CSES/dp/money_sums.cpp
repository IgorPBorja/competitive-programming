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

constexpr i64 MAXN = 100;
constexpr i64 MAXV = 1000;

bool dp[MAXN][MAXV * MAXN + 1];

void solve(){
    i64 n, x;
    cin >> n;
    cin >> x;
    dp[0][0] = true;
    dp[0][x] = true;

    for (i64 i = 1; i < n; i++){
        cin >> x;
        for (i64 s = 0; s <= i * MAXV; s++){
            dp[i][s] = dp[i - 1][s] || dp[i][s];
            dp[i][s + x] = dp[i - 1][s + x] || dp[i - 1][s] || dp[i][s + x]; 
        }
    }
    dp[n - 1][0] = false; // non-empty subsets

    i64 cnt = 0;
    for (i64 j = 0; j <= n * MAXV; j++){
        if (dp[n - 1][j]){
            ++cnt;
        }
    }
    cout << cnt << endl;
    for (i64 j = 0; j <= n * MAXV; j++){
        if (dp[n - 1][j]){
            cout << j << " ";
        }
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
