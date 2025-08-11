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

// only 1 round is ever needed
void solve(){
    // simulate round
    // applying a bulb is O(M)
    // checking ok is O(N)

    i64 n, m;
    cin >> n >> m;
    vector<i64> init(m, 0);
    
    i64 L;
    cin >> L;
    for (i64 i = 0; i < L; i++){
        i64 j;
        cin >> j;
        --j;
        init[j] = true;
    }

    i64 ans = -1;
    vector<vector<i64>> switches(n);
    for (i64 i = 0; i < n; i++){
        i64 k;
        cin >> k;
        for (i64 j = 0; j < k; j++){
            i64 p;
            cin >> p;
            --p;
            switches[i].emplace_back(p);
        }
    }
    for (i64 i = 0; i < 2 * n; i++){
        bool local_ok = true;
        const i64 k = switches[i % n].size();
        for (i64 j = 0; j < k; j++){
            const i64 p = switches[i % n][j];
            init[p] = !init[p];
        }
        for (i64 j = 0; j < m; j++) local_ok &= !init[j];
        if (local_ok && (ans == -1)){
            ans = i + 1;  // 1-indexed
        }
    }
    // might go up to 2n
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
