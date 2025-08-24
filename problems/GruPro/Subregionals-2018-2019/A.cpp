// #define TESTCASES
#define debug cout

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'

#define eb emplace_back
#define ep emplace
 
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

const i64 MOD = (i64)1e9 + 7;
const i64 MAXN = (i64)1e5 + 100;
vector<vector<i64>> factors;

vector<vector<i64>> sieve(){
    vector<i64> is_prime(MAXN + 1, true);
    vector<vector<i64>> factors(MAXN + 1);
    for (i64 i = 2; i <= MAXN; i++){
        if (!is_prime[i]) continue;
        factors[i].emplace_back(i);
        for (i64 j = 2 * i; j <= MAXN; j += i){
            is_prime[j] = false;
            factors[j].emplace_back(i);
        }
    }
    return factors;
}

// inclusive sum a + (a + 1) + ... + b, mod MOD
i64 inline s(i64 a, i64 b){
    return ((b * (b + 1)) / 2 - ((a - 1) * a) / 2) % MOD;
}

// compute sum(l <= q <= r, gcd(p, q) = 1)(aq + b)
// use inclusion exclusion: positive sign of even number of bits, else negative
// let p_1, ..., p_w be the primes that divide w
// and msk be mask in [0,2^w)
// Then is msk has even active bits, sum aq+b over multiples q of prod(p_i: i in mask)
// with l <= q <= r
// else, subtract
i64 coprime_function_sum(i64 p, i64 l, i64 r, i64 a, i64 b){
    i64 w = factors[p].size();
    // w is much smaller than log p
    // w * 2^w is much smaller than p, so it is not quadratic
    i64 total = 0;
    // starts positive at empty mask
    for (i64 msk = 0; msk < (1ll << w); msk++){
        i64 oddity = __builtin_popcount(msk) % 2;
        i64 sign = (oddity ? -1 : +1);
        i64 v = 1;
        for (i64 i = 0; i < w; i++) {
            if (msk & (1ll << i)) v *= factors[p][i];
        }
        i64 first = ((l + v - 1) / v), last = (r / v);
        if (first <= last){
            i64 deg1_term = (a * ((v * s(first, last)) % MOD)) % MOD;
            i64 deg0_term = (b * (last-first + 1)) % MOD;
            // %MOD on sum so MOD-sum is >=0
            total = (total + MOD + sign * ((deg0_term + deg1_term) % MOD)) % MOD;
        }
    }
    return total;
}

// x might be big, larger than 10^9
// but at most max(l,r)^2 = 10^10
// we must avoid overflow on long long
i64 ceil_isqrt(i64 x){
    i64 l = 0, r = min(x, (i64)1e6), ans = 1;
    while (l <= r){
        const i64 m = l + (r - l) / 2;
        i64 m2 = m * m;
        if (m2 >= x){
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

// x might be big, larger than 10^9
// but at most max(l,r)^2 = 10^10
// we must avoid overflow on long long
i64 floor_isqrt(i64 x){
    i64 l = 0, r = min(x, (i64)1e6), ans = 1;
    while (l <= r){
        const i64 m = l + (r - l) / 2;
        i64 m2 = m * m;
        if (m2 <= x){
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return ans;
}

// O(N log N + sum(p=1..N)w(p)*2^w(p))
// where w(p) = amount of distinct prime factors of p
void solve(){
    i64 n, m, l, r;
    cin >> n >> m >> l >> r;

    i64 ans = 0;
    for (i64 p = 1; p <= n - 1; p++){
        // p^2+q^2 >= l^2
        // ==> q = ceil(sqrt(l^2-p^2)) if p^2 <= l^2, else q >= 0 is enough
        // (but must use 1 instead of 0)
        // p^2+q^2 <= r^2
        // q <= floor(sqrt(r^2 - p^2)), if p^2 > r^2 then no solution
        // x-coord satisfies x+p <= N ==> 1 <= x <= N-p ==> N-p
        // y-coord satisfies, for a given q, y+q <= M ==> 1 <= y <= M-q ==> M-q
        if (p > r) break;
        i64 left = max(ceil_isqrt(max(l*l - p * p, (i64)0)), (i64)1);
        i64 right = min(floor_isqrt(r * r - p * p), m);
        if (left > right) continue;
        // we want (N - p) * sum(left<=q<=right, gcd(p,q)=1)(M-q)
        ans = (ans + (n - p) * coprime_function_sum(p, left, right, MOD - 1, m)) % MOD;
    }
    ans = (2 * ans) % MOD;  // case (-p, q), by symmetry
    if (l <= 1 && 1 <= r){
        // case p=0
        // NOT duplicated, because 0 = -0
        // only valid for q=1, for q>1 others will be blocked
        ans = (ans + n * (m - 1)) % MOD;

        // case q=0
        // NOT duplicated, because (p,0) and (-p,0) will be the same line
        // only valid for p=1, for p>1 others will be blocked
        ans = (ans + (n - 1) * m) % MOD;
    }
    cout << ans % MOD << endl;
}

 
signed main(){
    factors = sieve();  // > MAXN

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
