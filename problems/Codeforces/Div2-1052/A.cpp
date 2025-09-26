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
choose k as size

then value is
sum (k if c[x] >= k, 0)
*/

i64 f(const vector<i64>& cnt, i64 k){
    i64 tot = 0;
    const i64 n = cnt.size();
    for (i64 i = 0; i < n; i++){
        if (cnt[i] >= k) tot += k;
    }
    return tot;
}

// n * n * t = 5e6
void solve(){
    i64 n;
    cin >> n;
    vector<i64> cnt(n);
    for (i64 i = 0; i < n; i++){
        i64 x;
        cin >> x;
        --x;
        ++cnt[x];
    }
    i64 ans = 0;
    for (i64 k = 1; k <= n; k++){
        ans = max(ans, f(cnt, k));
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
