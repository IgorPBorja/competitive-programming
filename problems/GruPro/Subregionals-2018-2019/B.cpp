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
			debug << setw(3) << (v != INF ? to_string(v) : "INF") << " "; \
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

const i64 M = 100;
const i64 INF = (i64)2e18;

void solve(){
    // make (0,x), (x,0) and (x,x) have grundy number +INF
    // each player wants to force the other to get a losing position
    // (all grundy numbers = 0)
    // so game is equivalent to nim under normal play condition

    i64 n;
    cin >> n;
    
    vector<pair<i64, i64>> v(n);
    for (i64 i = 0; i < n; i++) cin >> v[i].first >> v[i].second;

    vector<vector<i64>> g(M + 1, vector<i64>(M + 1, -1));
    for (i64 i = 0; i <= M; i++){
        g[i][0] = g[0][i] = g[i][i] = INF;
    }

    for (i64 i = 0; i <= M; i++){
        for (i64 j = 0; j <= M; j++){
            if (g[i][j] != -1) continue;
            // neighbors = i + j + min(i,j)
            const i64 k = i + j + min(i,j) + 3;
            vector<i64> ok(k + 1, false);
            for (i64 d = 1; d <= i; d++){
                if (g[i - d][j] <= k) ok[g[i - d][j]] = true;
            }
            for (i64 d = 1; d <= j; d++){
                if (g[i][j - d] <= k) ok[g[i][j - d]] = true;
            }
            for (i64 d = 1; d <= min(i,j); d++){
                if (g[i - d][j - d] <= k) ok[g[i - d][j - d]] = true;
            }
            i64 mex = 0;
            for (; mex <= k; mex++){
                if (!ok[mex]) break;
            }
            g[i][j] = mex;
        }
    }

    // printgraph("g=", g);

    i64 final_g = 0;
    for (auto[a, b]: v){
        if (g[a][b] == INF){
            cout << "Y" << endl;
            return;
        } else {
            final_g ^= g[a][b];
        }
    }
    cout << ((final_g > 0) ? "Y" : "N") << endl;
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
