#define TESTCASES
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
d = gcd(a, m) = gcd(a + x, m)
<==> d | x and gcd(a / d + x / d, m / d) = 1
    given that gcd(a / d, m + d) = 1 already

Therefore let a' = a/d, m' = m/d
We need to find all 0 <= x < m' such that gcd(a' + x, m') = 1
    given that gcd(a', m') = 1 already

Let p1 ... pk be the primes that divide m'. Then we must have that
p_i does not divide a'+x for all i

We start with full interval [a', a'+m')
Then can brute over all bitmasks of primes since k is really small (inverse primorial)
and then remove/add (depending on mask parity according to inclusion/exclusion) all 
multiples of mask product over range.
*/

// closed [l, r]
i64 multiples_on_interval(i64 l, i64 r, i64 x){
    // from ceil(l/x) to floor(r/x), inclusive
    return (r / x) - ((l + x - 1) / x) + 1;
}

vector<i64> sieve(i64 MAXN) {
    vector<i64> primes;
    vector<i64> is_prime(MAXN + 1, true);
    for (i64 i = 2; i <= MAXN; i++){
        if (!is_prime[i]) continue;
        primes.emplace_back(i);
        for (i64 j = 2 * i; j <= MAXN; j += i){
            is_prime[j] = false;
        }
    }
    return primes;
}

void solve(){
    vector<i64> primes = sieve((i64)1e5 + 10);  // sqrt(M) where M is largest possible m

    i64 a, m;
    cin >> a >> m;
    i64 d = gcd(a, m);
    a /= d;
    m /= d;

    vector<i64> m_primes;
    i64 backup = m;
    for (i64 p: primes) {
        if (backup % p == 0) {
            m_primes.emplace_back(p);
            while (backup % p == 0) backup /= p;
        }
    }
    if (backup > 1) m_primes.emplace_back(backup);  // prime > sqrt(M)

    i64 ans = 0;
    const i64 k = m_primes.size();
    for (i64 msk = 0; msk < (1ll << k); msk++){
        i64 prod = 1;
        for (i64 i = 0; i < k; i++){
            if (msk & (1ll << i)) prod *= m_primes[i];
        }
        i64 sign = (__builtin_popcount(msk) % 2 == 0 ? 1 : -1);
        ans += sign * multiples_on_interval(a, a + m - 1, prod);
    }
    cout << ans << endl;
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
