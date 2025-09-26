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
f(x * y) = prod(a | x)prod(b | y)a * b = prod(a | x)[a ^ d(y) * f(y)] = f(x)^d(y) * f(y)^d(x)
*/

const i64 MOD = (i64)1e9 + 7;

i64 bexp(i64 a, i64 p){
    if (p == 0) return 1;
    else {
        const i64 b = bexp(a, p / 2);
        const i64 b2 = (b * b) % MOD;
        if (p % 2) return (a * b2) % MOD;
        else return b2;
    }
}

// returns (f(x), f(y))
pair<i64, i64> fd(const vector<pair<i64, i64>>& factorization, i64 idx = 0){
    if (idx == (i64)factorization.size()) return make_pair(1, 1);
    else {
        auto[fy, dy] = fd(factorization, idx + 1);
        auto[p, k] = factorization[idx];
        i64 fx = bexp(p, (k * (k + 1)) / 2);
        i64 dx = k + 1;
        i64 f = (bexp(fx, dy) * bexp(fy, dx)) % MOD;
        i64 d = (dy * dx) % (MOD - 1);  // use fermat little theorem
        return make_pair(f, d);
    }
}

void solve(){
    i64 n;
    cin >> n;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++) cin >> a[i];

    sort(all(a));
    vector<pair<i64, i64>> factorization;
    i64 p = a[0], cur = 1;
    for (i64 i = 1; i < n; i++){
        if (a[i] == p) ++cur;
        else {
            factorization.emplace_back(p, cur);
            p = a[i];
            cur = 1;
        }
    }
    factorization.emplace_back(p, cur);
    auto[f, _] = fd(factorization);
    cout << f << endl;
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

