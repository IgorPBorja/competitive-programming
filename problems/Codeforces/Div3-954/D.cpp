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

const i64 INF = 1e9;

vector<i64> min_expression(i64 b[], i64 n){
    vector<i64> dp(n);
    dp[0] = b[0];
    for (i64 i = 1; i < n; i++){
        // build last factor backwards
        i64 pow10 = 1;
        i64 x = 0;
        dp[i] = INF;
        for (i64 j = i; j >= 1; j--){
            x += pow10 * b[j];
            pow10 = min(INF, pow10 * (i64)10);
            dp[i] = min(dp[i], min(x * dp[j - 1], x + dp[j - 1]));
        }
        x += pow10 * b[0];
        dp[i] = min(dp[i], x);
    }
    return dp;
}

void solve(){
    i64 n;
    string s;

    cin >> n >> s;
    i64 a[n];
    for (i64 i = 0; i < n; i++) a[i] = s[i] - '0';

    if (n == 2){
        cout << a[0] * 10 + a[1] << endl;
        return;
    }
    
    vector<i64> prefix = min_expression(a, n);
    reverse(a, a + n);
    vector<i64> suffix = min_expression(a, n);
    reverse(a, a + n);

    i64 start = (a[0] * 10 + a[1]), end = (a[n - 2] * 10 + a[n - 1]);
    i64 start_exp = min(start * suffix[n - 3], start + suffix[n - 3]);
    i64 end_exp = min(end * prefix[n - 3], end + prefix[n - 3]);
    i64 ans = min(start_exp, end_exp);

    for (i64 i = 1; i + 2 < n; i++){
        i64 mid = a[i] * 10 + a[i + 1];
        i64 left = prefix[i - 1], right = suffix[n - i - 3];
        ans = min(ans, left + mid + right);
        ans = min(ans, left * mid + right);
        ans = min(ans, left + mid * right);
        ans = min(ans, left * mid * right);
    }

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
