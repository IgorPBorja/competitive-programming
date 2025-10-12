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
#define print(msg, v) debug << msg; for(auto it = v.begin(); it != v.end(); it++){debug << *it << " ";} debug << endl;
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
(i,j) will be aligned as a pair only once, and only if the distance is already right
at the start:

P[j] = i, P[i] = j
P[j] - P[i] = i - j mod n
<==> P[j] + j = P[i] + i mod n

also, each element will be a fixed point at least once, so semi-fixed as well
*/

void solve(){
    i64 n;
    cin >> n;
    vector<i64> p(n), c(n);
    for (i64 i = 0; i < n; i++){
        cin >> p[i];
        --p[i];
        ++c[(p[i] + i) % n];
    }
    i64 ans = n;
    for (i64 i = 0; i < n; i++){
        ans += (c[i] * (c[i] - 1));  // choose pairs and multiply by 2
    }
    // print("c=", c);
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
