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
    i64 n;
    cin >> n;
    i64 a[n], cnt[4] = {0, 0, 0, 0};

    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        ++cnt[a[i]];
    }

    double dp[n + 1][n + 1][n + 1];
    dp[0][0][0] = 0.0;
    for (i64 a3 = 0; a3 <= n; a3++){
        for (i64 a2 = 0; a2 + a3 <= n; a2++){
            for (i64 a1 = max(1 - a2 - a3, (i64)0); a1 + a2 + a3 <= n; a1++){
                i64 s = a1 + a2 + a3;
                // first solve the one-dimensional problem: expected value for N dishes with 1 sushi each
                // getting on k-th try
                // dp[i] = sum(k >= 0) (1-i/N)^k * (i / N) (k + 1 + dp[i-1])
                // = (i / N) * sum(k >= 0) (1 - i/N)^k * k + (i/N) * [sum(k >= 0) (1 - i/N)^k] * (1 + dp[i-1])
                // = (i/N) * sum(k >= 0) (1 - i/N)^k * k + (i/N) * N/i * (1 + dp[i - 1])
                // = (i/N) * sum(k >= 0) (1 - i/N)^k * k + 1 + dp[i - 1]
                // Note that sum k * x^k = x * (d/dx)(sum x^k) = x * (d/dx)(1-x)^{-1}
                // = x * (1-x)^{-2} = x / (1 - x)^2
                // Therefore (i/N) * sum(k >= 0) (k+1)(1 - i/N)^k = 1 / (i/N) + (1-i/N)/(i/N)^2 = N^2/i^2
                // and we conclude that dp[i] = (i/N) * N^2/i^2 + (i/N) * dp[i-1] / (i/N) = N/i + dp[i - 1]

                // probability of first k equal to zero then hitting one with i sushi
                // = (1 - s/N)^k * a_i
                // contribution: sum(k >= 0) (1-s/N)^k * (a_i / N) (k + 1 + corresponding dp)
                // = (ai/N)(N^2/s^2 + (N/s)corresponding dp)
                // = (ai/s)(N/s + corresponding dp)
                // since we sum over all ai and s > 0
                // = (s/s) * (N/s) + sum (ai/s) * corresponding dp
                // = (N/s) + sum(ai / s) * corresponding dp
                double prob[4] = {
                    0.0,
                    (double)a1 / (double)s,
                    (double)a2 / (double)s,
                    (double)a3 / (double)s
                };
                dp[a3][a2][a1] = (double)n / (double)s;
                if (a1 > 0) {
                    dp[a3][a2][a1] += prob[1] * dp[a3][a2][a1 - 1];
                }
                if (a2 > 0) {
                    // if a2 > 0 then a1 < n
                    dp[a3][a2][a1] += prob[2] * dp[a3][a2 - 1][a1 + 1];
                }
                if (a3 > 0){
                    // if a3 > 0 then a2 < n
                    dp[a3][a2][a1] += prob[3] * dp[a3 - 1][a2 + 1][a1];
                }
            }
        }
    }
    cout << fixed << setprecision(12) << dp[cnt[3]][cnt[2]][cnt[1]] << endl;
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
