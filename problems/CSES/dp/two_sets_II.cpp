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

const i64 MOD = (i64)1e9 + 7;

i64 bexp_mod(i64 a, i64 p){
    if (p == 0){
        return 1;
    } else {
        i64 m = bexp_mod(a, p / 2);
        if (p % 2 == 0){
            return (m * m) % MOD;
        } else {
            return (((m * m) % MOD) * a) % MOD;
        }
    }
}

void solve(){
    i64 n;
    cin >> n;

    // sum ranges from -n(n+1)/2 to +n(n+1)/2 ==> n(n+1)+1
    // offset is n(n+1)/2
    i64 off = (n * (n + 1)) / 2;
    i64 dp[2][n * (n + 1) + 1];
    for (i64 j = 0; j < n * (n + 1) + 1; j++){
        dp[0][j] = 0;
    }
    for (i64 j = 0; j < n * (n + 1) + 1; j++){
        dp[1][j] = 0;
    }

    dp[0][1 + off] = 1;
    dp[0][-1 + off] = 1;

    for (i64 i = 2; i <= n; i++){
        // clear from previous transitions!
        memset(dp[(i - 1) % 2], 0, (2 * off + 1) * sizeof(i64));
        for (i64 j = - ((i * (i + 1)) / 2); j <= (i * (i + 1)) / 2; j++){
            if (j - i >= -off){
                dp[(i - 1) % 2][j + off] = (dp[(i - 1) % 2][j + off] + dp[(i - 2) % 2][j + off - i]) % MOD;
            }
            if (j + i <= off){
                dp[(i - 1) % 2][j + off] = (dp[(i - 1) % 2][j + off] + dp[(i - 2) % 2][j + off + i]) % MOD;
            }
        }
    }
    
    // divide by 2 (mod MOD) because of symmetry
    cout << (dp[(n - 1) % 2][0 + off] * bexp_mod(2, MOD - 2)) % MOD << endl;
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
