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

const i64 MOD = (i64)1e9 + 7;

void solve(){
    string k;
    i64 d;
    cin >> k;
    cin >> d;

    i64 dp[k.size() + 1][d]; // dp[i][j] = how many integers, mod MOD, of length i have digitsum = j mod d
    
    for (i64 i = 0; i < d; i++){
        dp[0][i] = 0;
        dp[1][i] = 0;
    }
    dp[0][0] = 1;
    // DOES consider leading zeros this way (since i starts at 0)
    for (i64 i = 0; i < 10; i++){
        dp[1][i % d] = (dp[1][i % d] + 1) % MOD;
    }
    for (i64 s = 2; s <= k.size(); s++){
        for (i64 m = 0; m < d; m++){
            dp[s][m] = 0;
            for (i64 last = 0; last < 10; last++){
                // the last % d is because we can have d < 10
                dp[s][m] = (dp[s][m] + dp[s - 1][(m + d - (last % d)) % d]) % MOD;
            }
        }
    }

    i64 ans = 0, prefix_mod = 0;
    for (i64 p = 0; p < k.size(); p++){
        // length of longest common prefix, going up to second to len(k) - 1 
        if (p > 0) {
            prefix_mod = (prefix_mod + (k[p - 1] - '0')) % d;
        }
        for (i64 first = 0; first < (k[p] - '0'); first++){
            // the first % d is because we can have d < 10
            i64 target = (d - prefix_mod + d - (first % d)) % d;
            ans = (ans + dp[k.size() - p - 1][target]) % MOD;
        }
    }
    // edge case 2: K itself
    prefix_mod = (prefix_mod + (k[k.size() - 1] - '0')) % d;
    if (prefix_mod == 0) ans = (ans + 1) % MOD;

    ans = (ans + MOD - 1) % MOD;  // exclude 0
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
