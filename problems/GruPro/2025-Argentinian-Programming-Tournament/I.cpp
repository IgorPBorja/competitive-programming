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

void solve(){
    i64 n, m;
    cin >> n >> m;
    vector<i64> q(n);
    i64 g = 0;
    for (i64 _ = 0; _ < m; _++){
        i64 x, y;
        cin >> x >> y;
        vector<i64> a(n);
        i64 cnt[2] = {0, 0};
        for (i64 i = 0; i < n; i++) {
            cin >> a[i];
            --a[i];
            ++cnt[a[i]];
        }
        // print("a=", a);
        // cerr << "cnt=" << cnt[0] << " " << cnt[1] << endl;
        if (x / (cnt[0] + 1) >= y){
            // cerr << "chose 1" << endl;
            // cerr << "adding dx=" << x / (cnt[0] + 1) << " or y=" << y << endl;
            for (i64 i = 0; i < n; i++) {
                if (a[i] == 0) q[i] += x / (cnt[0] + 1);
                else q[i] += y;
            }
            g += x / (cnt[0] + 1);
        } else {
            // cerr << "chose 2" << endl;
            // cerr << "adding dx=" << (cnt[0] != 0 ? x / cnt[0] : 0) << " or y=" << y << endl;
            for (i64 i = 0; i < n; i++) {
                if (a[i] == 0) q[i] += x / cnt[0];
                else q[i] += y;
            }
            g += y;
        }
    }
    for (i64 i = 0; i < n; i++) cout << q[i] << " ";
    cout << g << endl;
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
