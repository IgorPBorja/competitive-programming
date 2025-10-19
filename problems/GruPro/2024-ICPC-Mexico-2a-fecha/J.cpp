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
    i64 n, m;
    cin >> n >> m;
    vector<vector<i64>> a(n, vector<i64>(n, 0));

    for (i64 i = 0; i < m; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        a[u][v] = a[v][u] = 1;
    }

    if (n == 1){
        cout << "NO" << endl;
        return;
    }

    vector<pair<i64, i64>> edges;
    vector<i64> A(n / 2), B(n - n / 2);
    iota(all(A), 0);
    iota(all(B), n / 2);
    for (i64 i: A){
        for (i64 j: A){
            if (i < j && !a[i][j]){
                edges.emplace_back(i, j);
            }
        }
    }
    for (i64 i: B){
        for (i64 j: B){
            if (i < j && !a[i][j]){
                edges.emplace_back(i, j);
            }
        }
    }
    cout << "YES" << endl;
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
