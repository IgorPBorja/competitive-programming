// #define TESTCASES

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
    i64 n;
    cin >> n;
    vector<i64> f(n), g(n);
    vector<i64> vis1(n, false), vis2(n, false);

    for (i64 i = 0; i < n; i++){
        cin >> f[i];
        --f[i];
    }
    for (i64 i = 0; i < n; i++){
        cin >> g[i];
        --g[i];
    }
    i64 ans = 0;
    for (i64 i = 0; i < n; i++){
        if (!vis1[i]){
            i64 cur = 1, v = i;
            vis1[i] = true;
            while (f[v] != i){
                ++cur;
                v = f[v];
                vis1[v] = true;
            }
            ans += cur - 1;
        }
        if (!vis2[i]){
            i64 cur = 1, v = i;
            vis2[i] = true;
            while (g[v] != i){
                ++cur;
                v = g[v];
                vis2[v] = true;
            }
            ans += cur - 1;
        }
    }
    cout << ans << endl;
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
