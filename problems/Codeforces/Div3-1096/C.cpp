#define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		cerr << "G[" << u << "]="; \
		for (i64 v: G[u]) { \
			cerr << v << " "; \
		} \
		cerr << endl; \
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
    vector<i64> m2, m3, m6, other;
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++) cin >> a[i];
    for (i64 i = 0; i < n; i++){
        if (a[i] % 6 == 0) m6.emplace_back(a[i]);
        else if (a[i] % 2 == 0) m2.emplace_back(a[i]);
        else if (a[i] % 3 == 0) m3.emplace_back(a[i]);
        else other.emplace_back(a[i]);
    }
    vector<i64> b;
    b.reserve(n);
    for (i64 x: m6) b.emplace_back(x);
    for (i64 x: m2) b.emplace_back(x);
    for (i64 x: other) b.emplace_back(x);
    for (i64 x: m3) b.emplace_back(x);

    for (i64 x: b) cout << x << " ";
    cout << endl;
}
 
signed main(){
	fastio;
	int t = 1;
#ifdef TESTCASES
	cin >> t;
#endif
	while (t--){
		solve();
	}
}
