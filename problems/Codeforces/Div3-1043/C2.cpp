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

void solve(){
    // x + x * 10^k
    // so n = x(10^k + 1)
    i64 n, k;
    cin >> n >> k;
    vector<i64> p3, c3;
    i64 x = 1, e = 0;
    while (x <= n){
        i64 c = 3 * x + e * (x / 3);
        p3.emplace_back(x);
        c3.emplace_back(c);
        x *= 3;
        ++e;
    }

    // 3-base 
    vector<i64> used(p3.size(), (i64)0);
    e = 0;
    i64 cost = 0;
    while (n > 0){
        i64 r = n % 3;
        cost += c3[e] * r;
        used[e] = r;
        k -= r;
        n /= 3;
        ++e;
    }
    if (k < 0){
        cout << -1 << endl;
        return;
    }
    // now try to reduce
    // reducing early ==> higher impact
    for (i64 i = p3.size() - 1; i > 0 && k >= 2; i--){
        // introduces 2 more per 
        i64 delta = min(used[i], k / 2);
        cost -= delta * c3[i];
        cost += delta * c3[i - 1] * 3;
        used[i - 1] += 3 * delta;
        used[i] -= delta;
        k -= 2 * delta;
    }
    cout << cost << endl;
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
