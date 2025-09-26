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

constexpr i64 MAXN = (i64)1.6e7;

int spf[MAXN + 1];  // here int is critical, i64 might give MLE b/c mem limit is tight

void sieve(){
    bitset<MAXN + 1> is_composite{0};
    for (i64 i = 2; i <= MAXN; i++){
        if (is_composite[i]) continue;
        spf[i] = i;
        for (i64 j = 2 * i; j <= MAXN; j += i){
            if (!spf[j]) spf[j] = i;
            is_composite.set(j, true);
        }
    }
}

void solve(){
    /*
    divide all by gcd first

    then gcd(a1, ..., an) = 1 after update
    To get some prime p we need to remove all values not divisible by p

    So answer is min(#{a_i: a_i != 0 mod p}) over all primes p

    we can't sieve all, so we have 0
    */

    sieve();

    i64 n, g = 0;
    cin >> n;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        g = gcd(g, a[i]);
    }
    for (i64 i = 0; i < n; i++) a[i] /= g;

    bool all_1 = true;
    for (i64 i = 0; i < n; i++) all_1 &= (a[i] == 1);
    if (all_1) {
        cout << -1 << endl;  // only impossible case since gcd is 1 after transform
        return;
    }

    map<i64, i64> included;
    // O(n (log C + inverse_primorial(C) * log C)) < O(n log^2 C)
    for (i64 i = 0; i < n; i++){
        // printmsg("factors a[" << i << "]=" << a[i] << " is=", factors[i].begin(), factors[i].end());
        while (a[i] != 1){
            i64 p = spf[a[i]];
            ++included[p];
            while (a[i] % p == 0) a[i] /= p;
        }
    }
    i64 ans = n - 1;
    for (auto [_, c]: included){
        ans = min(ans, n - c);  // has to remove n-c to get prime p on gcd
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
