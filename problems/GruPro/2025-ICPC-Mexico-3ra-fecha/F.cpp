// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		cerr << "G[" << u << "]="; \
		for (auto v: G[u]) { \
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

/*
1 is wall, 0 is free
UDLR
robot ignores **specific** bad instructions, and stays still and skips to the next individual instruction in the order

*/

// applies order to (i,j) and returns end position and cost (effective movements)
tuple<i64, i64, i64> apply_order(i64 i, i64 j, vector<vector<i64>>& grid, string& order){
    const i64 n = grid.size(), m = grid[0].size();
    auto is_valid = [&n, &m, &grid](i64 x, i64 y){
        return (0 <= x) && (x < n) && (0 <= y) && (y < m) && (grid[x][y] == 0);
    };

    i64 cost = 0;
    for (char c: order){
        i64 ii = i, jj = j;
        if (c == 'U'){
            --ii;
        } else if (c == 'D'){
            ++ii;
        } else if (c == 'R') {
            ++jj;
        } else if (c == 'L') {
            --jj;
        }
        if (is_valid(ii, jj)) {  // move
            i = ii;
            j = jj;
            ++cost;
        } else {
            // do nothing
        }
    }
    return make_tuple(i, j, cost);
}

const i64 INF = 2e18;

void solve(){
    i64 n, m;
    cin >> n >> m;
    i64 x0, y0, xf, yf;
    vector<vector<i64>> grid(n, vector<i64>(m)), dist(n, vector<i64>(m, INF));

    for (i64 i = 0; i < n; i++){
        string s;
        cin >> s;
        for (i64 j = 0; j < m; j++){
            grid[i][j] = s[j] - '0';
        }
    }
    cin >> x0 >> y0;
    cin >> xf >> yf;

    i64 k;
    cin >> k;
    vector<vector<vector<tuple<i64, i64, i64>>>> adj(n, vector<vector<tuple<i64, i64, i64>>>(m));
    for (i64 _ = 0; _ < k; _++){
        string order;
        cin >> order;
        // cerr << "order=" << order << endl;
        for (i64 i = 0; i < n; i++){
            for (i64 j = 0; j < m; j++){
                if (grid[i][j] == 1) continue;
                auto[ii, jj, w] = apply_order(i, j, grid, order);
                if (make_pair(ii, jj) != make_pair(i, j)){  // no self loops
                    adj[i][j].emplace_back(w, ii, jj);
                }
            }
        }
    }

    min_pq<tuple<i64, i64, i64>> pq;
    pq.emplace(0, x0, y0);
    while (!pq.empty()){
        auto[d, i, j] = pq.top();
        pq.pop();
        if (d >= dist[i][j]) continue;
        dist[i][j] = d;
        for (auto[w, x, y]: adj[i][j]){
            if (dist[i][j] + w < dist[x][y]){
                pq.emplace(dist[i][j] + w, x, y);
            }
        }
    }
    cout << ((dist[xf][yf] < INF) ? dist[xf][yf] : -1) << endl;
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
