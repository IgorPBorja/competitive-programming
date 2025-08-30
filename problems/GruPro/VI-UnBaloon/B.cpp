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

i64 MAXN = (i64)1e6 + 10;
const i64 MOD = (i64)1e9 + 7;
vector<i64> fat(MAXN + 1), ifat(MAXN + 1);

i64 bexp(i64 a, i64 p, i64 mod){
    if (p == 0) return 1;
    else {
        const i64 b = bexp(a, p / 2, mod);
        const i64 b2 = (b * b) % mod;
        if (p % 2 == 0) return b2;
        else return (a * b2) % mod;
    }
}

i64 f(i64 n, i64 k){
    // debug << "at k =" << k << endl;
    if (k == 0){
        return 0;  // empty sum
    }
    
    i64 last = 0;
    // when last = k we have 2^(k+1)-1 options
    while (k > (1ll << (last + 1)) - 1){
        ++last;
    }

    // debug << "last=" << last << endl;

    // last is guaranteed
    // see offset against previous block
    return (bexp(n, last, MOD) + f(n, k - (1ll << last))) % MOD;
}

void solve(){
    i64 n, k;
    cin >> n >> k;
    cout << f(n, k) << endl;
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
