#define TESTCASES
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

/*
If every number in [l,...,r] divides n then n is a multiple of prod(p prime) max(i=l..r)vp(i)


Lemma: max(i=1..r-l+1) vp(i) <= max(i=l..r)vp(i) for every prime p

Proof:
Suppose k = max(i=1..r-l+1)vp(i). Then, since the mod sequence a[i] := i mod p^k starts at 1,
for it to reach 0 we must have p^k <= r-l+1. Therefore, for any interval [l,..,r], there will be
a multiple of p^k in it, and max(i=l..r)vp(i) >= k.

It easy to see prod(p prime)max(i=1..r-l+1)vp(i) grows fast. r-l+1 <= 1000 for sure.
To see that, notice max vp(i) ~ log_p(r-l+1),

prod(p prime, p <= x)p^log_p(x) ~ x^#(p prime, p <= x) ~ x^(x/log x) (asymptotically. in practice it starts smaller)
*/

const i64 MAXN = 1000;
vector<vector<pair<i64, i64>>> factors;

void sieve(){
    factors.resize(MAXN + 1);
    vector<i64> is_prime(MAXN + 1, 1);
    for (i64 i = 2; i <= MAXN; i++){
        if (!is_prime[i]) continue;
        factors[i].emplace_back(i, i);
        for (i64 j = 2 * i; j <= MAXN; j += i){
            is_prime[j] = false;
            i64 i_pow = i;
            while (j % (i_pow * i) == 0){
                i_pow *= i;
            }
            factors[j].emplace_back(i, i_pow);
        }
    }
}


void solve(){
    i64 n;
    cin >> n;
    i64 cur = 1, ans = 1;
    map<i64, i64> prime_powers;
    for (i64 x = 2; x <= MAXN; x++){
        for (auto[p, pk]: factors[x]){
            if (prime_powers[p] == 0){
                cur *= pk;
                prime_powers[p] = pk;
            } else if (pk > prime_powers[p]){
                cur *= pk/prime_powers[p];
                prime_powers[p] = pk;
            }
        }
        if (n % cur == 0){
            ans = x;
        } else {
            break;
        }
    }
    cout << ans << endl;
}
 
signed main(){
    sieve();

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
