// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

/*

*/

const i64 MOD = (i64)998244353;

i64 bexp(i64 a, i64 p){
    if (p == 0) return 1;
    else {
        i64 b = bexp(a, p / 2);
        i64 b2 = (b * b) % MOD;
        if (p % 2 == 0) return b2;
        else return (a * b2) % MOD;
    }
}

i64 inv(i64 a) { return bexp(a, MOD - 2); }

i64 divmod(i64 a, i64 b) { return (a * inv(b)) % MOD; }

/*
Let the last tower active be i. Then we are forced to take power n + 1 - i on it to cover n
==> we must have n + 1 - i <= i. Then, letting delta=n+1-i, we are covering [i-delta+1..n]
and we need to find a subcover of [1..i-delta] without covering 0 or i-delta+1.

This reduces to the same subproblem on i-delta. Then

dp[n] = sum(n+1-i <= i <= n) Pr(i is the last active tower and everyone on the window is turned off) * dp[i - delta]
dp[n] = sum(floor(n/2) + 1 <= i <= n) 1/2^{2 * delta - 1} * dp[2i - (n + 1)]
        --> since window in (i-delta, i+delta), open interval
dp[n] = sum(floor(n/2) + 1 <= i <= n) 1/2^{2n + 1 - 2i} * dp[2i - (n + 1)]

(NOTE: if someone on the window is turned on, there will be duplication)

We can note that 2i - (n+1) will start at (n+1) mod 2 and go from there, and the 2n+1-2i exponent
will start at 2n + 1 - 2floor(n/2) - 2 = 2*ceil(n/2) - 1 and decrease by 2 each step
until 1 (which happens at i=n). So we have

dp[n] = sum(i=0..ceil(n/2)-1) 1/2^{2*ceil(n/2) - 1 - 2i} dp[2i + (n+1 mod 2)]

Note that dp[n+2] = sum
dp[n+2] = sum(i=0..ceil(n/2)) 1/2^{2*ceil(n/2) + 2 - 1 - 2i} dp[2i + (n+3 mod 2)]
= (1/2^2)[sum(i=0..ceil(n/2)-1) 1/2^{2*ceil(n/2) - 1 - 2i} dp[2i + (n+1 mod 2)]] + 1/2 * dp[2 * ceil(n/2) + (n+3 mod 2)]
= (1/4)dp[n] + (1/2)dp[2 * ceil(n/2) + (n+3 mod 2)]

But this only works when n >= 2 (WHY?)

so we have a O(1) transition step!
*/

void solve(){
    i64 n;
    cin >> n;
    vector<i64> dp(max(n, (i64)3) + 1);
    dp[0] = 1;  // empty set of targets, always possible
    dp[1] = inv(2);
    dp[2] = inv(4);
    dp[3] = inv(4);

    for (i64 i = 2; i <= n - 2; i++){
        dp[i + 2] = ( divmod(dp[i], 4) + divmod(dp[2 * ((i + 1) / 2) + ((i + 3) % 2)], 2) ) % MOD;
    }
    cout << dp[n] << endl;
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

