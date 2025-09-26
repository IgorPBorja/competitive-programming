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
    // earliest sign change
    // if there is a k-length starting with positive
    // and k-length starting with negative then there is a k+1
    // starting with the sign of the earliest
    // So taking earliest sign work

    vector<i64> sign_blocks;
    i64 n;
    cin >> n;
    vector<i64> a(n);
    cin >> a[0];
    i64 sign = (a[0] > 0 ? +1 : -1);
    i64 cur = a[0];
    for (i64 i = 1; i < n; i++) {
        cin >> a[i];
        i64 new_sign = (a[i] > 0 ? +1 : -1);
        if (new_sign != sign){
            sign_blocks.emplace_back(cur);
            cur = a[i];
            sign = new_sign;
        } else {
            cur = max(cur, a[i]);
        }
    }
    sign_blocks.emplace_back(cur);
    // cout << sign_blocks.size() << endl;
    cout << accumulate(all(sign_blocks), (i64)0) << endl;
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
