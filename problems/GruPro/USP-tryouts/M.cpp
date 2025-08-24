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

void solve(){
    i64 n, d;
    cin >> n >> d;
    vector<i64> a(n);
    vector<pair<i64, i64>> nonzero;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        if (a[i] != 0) nonzero.emplace_back(i, a[i]);
    }
    if (nonzero.size() >= 2 || (nonzero.size() == 1 && nonzero[0].second >= d)){
        i64 idx = 0, cur = 0;
        for (i64 i = 0; i < d; i++){
            cout << nonzero[idx].first + 1 << " ";
            ++cur;
            if (cur == nonzero[idx].second){
                idx = 1 - idx;
                cur = 0;
            }
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }
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
