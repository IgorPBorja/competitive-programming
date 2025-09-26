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
NOTE: an element can't hold an element that already holds someone (no chains are possible)
*/

void solve(){
    i64 n;
    cin >> n;

    multiset<i64> ms;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    sort(all(a));
    // greedily it is best to make the extra be on the left side
    // so r starts higher and there is better chance of pairing
    i64 cnt = (n + 1) / 2;
    i64 r = (n + 1) / 2;
    for (i64 l = 0; l < n / 2; l++){
        while (r < n && a[r] < 2 * a[l]) ++r;
        if (r < n) {
            // OK
        } else {  // can't pair
            ++cnt;
        }
        ++r;
    }
    for (; r < n; r++) ++cnt;
    cout << cnt << endl;
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
