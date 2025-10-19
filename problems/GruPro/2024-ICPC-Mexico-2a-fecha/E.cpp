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
    vector<i64> a(n);
    vector<pair<i64, i64>> v(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        v[i] = make_pair(a[i], i);
    }
    sort(all(v));

    vector<i64> active;
    vector<pair<i64, i64>> edges;
    for (auto[x, i]: v){
        // try to make i itself
        if (x - 1 > active.size()){  // cant make it
            cout << -1 << endl;
            return;
        }
        for (i64 j = 0; j < x - 1; j++) edges.emplace_back(i, active[j]);
        active.emplace_back(i);
    }
    cout << edges.size() << endl;
    for (auto[u, v]: edges){
        cout << u + 1 << " " << v + 1 << endl;
    }
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
