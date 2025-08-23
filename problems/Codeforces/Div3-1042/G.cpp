#define TESTCASES
#define debug cout

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
Let f(n) be the multiplier obtained by removing [1,2,...,n] from a set S where [1,2,...,n] is in S

Then f(n) = n f(n-1)^2 since you solve [1,...,n-1], then remove n and solve [1,...,n-1] again
Therefore by induction

f(n) = prod(i=1..n) i^(2^{n-i})

number of operations for this is ops(n) := 1 + 2*ops(n-1) ==> ops(n) = 2^n - 1

So we can only solve at most f(n) where n = O(log(k)). We can precompute f[x] for x <= O(log k)
in O(log k)

We skip compress operations as much as possible, and open as-needed.

At worst you will process imediately (by operation compression) N-1 elements in O(N log N)
then open the last, of value open x=O(log K) into [1,...,x-1]
then solve 1..x-2 and open x-1 into [1,...,x-2] and so forth

so final complexity is O(N log N + log^2 k)
*/
const i64 MOD = (i64)1e9 + 7;
const i64 INF = (i64)2e18;

// ops(n) = operations to solve a single n
// Let ops'(n) = operations to solve [1,..,n]
// Then ops'(n) = 1 + 2 * ops'(n-1) ==> ops'(n) = 2^n - 1
// so ops(n) = 1 + ops'(n - 1) = 2^{n - 1}
i64 ops(i64 n){
    // 2^32 > 4e9
    if (n > 32) return INF;
    else return (1ll << (n - 1));
}

void solve(){
    // pre-compute f(n) = multiplier for removing [1,..,n]
    // and then g(n) = multiplier for removing [n]
    const i64 LOGN = 45;
    vector<i64> f(LOGN + 1), g(LOGN + 1);
    f[1] = g[1] = 1;
    for (i64 i = 2; i <= LOGN; i++){
        f[i] = (i * ((f[i-1] * f[i-1]) % MOD)) % MOD;
        g[i] = (i * f[i - 1]) % MOD;
    }

    i64 n, k;
    cin >> n >> k;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++) cin >> a[i];

    set<i64> s;
    for (i64 x: a) s.insert(x);

    i64 ans = 1;
    while (k > 0 && s.size() > 0){
        i64 x = *s.begin();
        s.erase(s.begin());  // x will be used anyway
        if (ops(x) <= k){
            // guaranteed x = O(log(k)) so calculating f(x) is fine
            k -= ops(x);
            ans = (ans * g[x]) % MOD;
        } else {
            // break down step
            ans = (ans * x) % MOD;
            --k;
            // guaranteed this loop won't run for more than O(log(k))
            i64 total_ops = 0;
            // micro-optimization: skip 1 layer of "recursion" by pre-solving here
            for (i64 y = 1; y < x; y++){
                s.insert(y);        
                total_ops += ops(y);
                if (total_ops >= k){
                    break;  // insert to get just above k ops
                }
            }
        }
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

