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
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

const i64 INF = 2e18;

void solve(){
    string s;
    i64 n;
    cin >> s >> n;
    const i64 m = s.size(); 
    // precomp pow
    i64 p10[m + 1];
    p10[0] = 1;
    for (i64 i = 1; i <= m; i++){
        p10[i] = (p10[i - 1] * 10) % n;
    }

    bool dp[m + 1][n];
    i64 digit[m + 1][n];
    
    dp[m][0] = true;
    for (i64 i = 1; i < n; i++) dp[m][i] = false;

    for (i64 i = m - 1; i >= 0; i--){
        for (i64 t = 0; t < n; t++){
            if (s[i] != '?'){
                const i64 d = s[i] - '0';
                const i64 new_t = (t + n - (p10[m - 1 - i] * d) % n) % n;
                dp[i][t] = dp[i + 1][new_t];
                if (dp[i][t]){
                    // save parent
                    digit[i][t] = d;
                }
            } else {
                dp[i][t] = false;
                for (i64 d = (i == 0? 1 : 0); d < 10; d++){
                    const i64 new_t = (t + n - (p10[m - 1 - i] * d) % n) % n;
                    if (!dp[i][t] && dp[i + 1][new_t]){
                        // save smallest parent
                        digit[i][t] = d;
                    }
                    dp[i][t] |= dp[i + 1][new_t];
                }
            }
        }
    }

    if (!dp[0][0]){
        cout << "*" << endl;
    } else {
        string ans;
        i64 t = 0;
        for (i64 i = 0; i < m; i++){
            ans.push_back((char)('0' + digit[i][t]));
            t = (t + n - (p10[m - 1 - i] * digit[i][t]) % n) % n;
        }
        cout << ans << endl;
    }
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
