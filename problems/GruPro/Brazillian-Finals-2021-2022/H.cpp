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

/*
because the even positions are fixed, put odd element 2j+1 into 2i+1
has a fixed cost regardless of the remainder of the configuration

So we can build a complete bipartite graph mapping 2j+1 (as an element) to 2i+1 (as a position)
with edge costs, and calculate min cost maximum matching.

Complexity of hungarian algorithm should be |A| * |B| * min(|A|, |B|) = n^3/8
*/

const i64 INF = 1e18;

// FROM KACTL
pair<i64, vector<i64>> hungarian(const vector<vector<i64>> &a){
    if (a.empty()) return {0, {}};
    i64 n = a.size() + 1, m = a[0].size() + 1;
    vector<i64> u(n), v(m), p(m), ans(n - 1);
    for (i64 i = 1; i < n; i++){
        p[0] = i;
        i64 j0 = 0;
        vector<i64> dist(m, INF), pre(m, -1);
        vector<i64> done(m + 1, false);
        do {  // dijkstra
            done[j0] = true;
            i64 i0 = p[j0], j1, delta = INF;
            for (i64 j = 1; j < m; j++) if (!done[j]){
                auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
                if (dist[j] < delta) delta = dist[j], j1 = j;
            }
            for (i64 j = 0; j < m; j++){
                if (done[j]) u[p[j]] += delta, v[j] -= delta;
                else dist[j] -= delta;
            }
            j0 = j1;
        } while (p[j0]);
        while (j0) { // update alternating path
            i64 j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    for (i64 j = 1; j < m; j++) if (p[j]) ans[p[j] - 1] = j - 1;
    return {-v[0], ans};
}

void solve(){
    i64 n;
    cin >> n;
    vector<vector<i64>> L(n, vector<i64>(n));
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < n; j++){
            cin >> L[i][j];
        }
    }

    i64 odd = (n + 1) / 2;
    vector<vector<i64>> cost(odd, vector<i64>(odd));
    for (i64 element = 0; element < n; element += 2){  // odd elements, since it is 1-indexed
        for (i64 pos = 0; pos < n; pos += 2){
            cost[element / 2][pos / 2] = 0;
            if (pos > 0) cost[element / 2][pos / 2] += L[element][pos - 1];
            if (pos + 1 < n) cost[element / 2][pos / 2] += L[element][pos + 1];
        }
    }
    auto[mincost, _] = hungarian(cost);
    cout << mincost << endl;
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
