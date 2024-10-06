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

const i64 MOD = 1e9 + 7;

i64 safe_mod(i64 n){
    if (n < 0){
        i64 c = (-n + MOD - 1) / MOD; // ceil
        return (n + c * MOD) % MOD;
    } else {
        return n % MOD;
    }
}

i64 max_subarray(vector<i64>& a){
    i64 n = a.size();
    vector<i64> dp(n); // max sum ending at i
    dp[0] = a[0];

    for (i64 i = 1; i < n; i++){
        dp[i] = a[i] + max(dp[i - 1], (i64)0);
    }

    i64 ans = 0;
    for (i64 i = 0; i < n; i++){
        ans = max(ans, dp[i]);
    }
    return safe_mod(ans);
}

i64 bexp(i64 a, i64 p){
    if (p == 0){
        return 1;
    } else {
        i64 r = p % 2;
        i64 m = bexp(a, p / 2);
        if (r % 2 == 0){
            return (m * m) % MOD;
        } else {
            return (((m * m) % MOD) * a) % MOD;
        }
    }
}

void solve(){
    i64 n, k;
    cin >> n >> k;
    
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    i64 s = 0;
    for (i64 x: a){
        s += x;
    }
    s = safe_mod(s);

    i64 m = max_subarray(a);
    i64 blown_m = (bexp(2, k) * m) % MOD;
    // cout << "m=" << m;
    i64 outer = (s + MOD - m) % MOD;
    // cout << "outer=" << outer << endl;
    cout << (outer + blown_m) % MOD << endl;
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
