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
    i64 n, m, k, u1, u2, v1, v2;
    cin >> n >> m >> k;
    vector<vector<i64>> grid(n, vector<i64>(vector<i64>(m, 0)));
    for (i64 i = 0; i < k; i++){
        i64 x, y;
        cin >> x >> y;
        --x; --y;
        grid[x][y] = i + 1;
    }
    cin >> u1 >> v1 >> u2 >> v2;
    --u1; --v1; --u2; --v2;

    auto check = [&grid, u1, v1, u2, v2, n, m](i64 h){
        #define inside(i, j) (u1 <= i && i <= u2 && v1 <= j && j <= v2)
        #define ok(i, j) (0 <= i && i < n && 0 <= j && j < m)
        const i64 dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

        queue<pair<i64, i64>> q;
        for (i64 i = u1; i <= u2; i++) {
            for (i64 j = v1; j <= v2; j++){
                if (grid[i][j] > h) return false;
                q.emplace(i, j);
            }
        }
        vector<vector<i64>> vis(n, vector<i64>(m, false));
        i64 filled_inside = 0, empty_outside = 0;
        while (!q.empty()){
            auto[i, j] = q.front();
            q.pop();
            if (vis[i][j]) continue;
            vis[i][j] = true;
            filled_inside += (inside(i, j) && (grid[i][j] > 0));
            empty_outside += (!inside(i, j) && (grid[i][j] == 0));
            for (i64 k = 0; k < 4; k++){
                i64 ii = i + dx[k], jj = j + dy[k];
                if (!ok(ii, jj)) continue;
                if (vis[ii][jj]) continue;
                if (grid[ii][jj] > h) continue;
                q.emplace(ii, jj);
            }
        }
        // cout << "filled_inside=" << filled_inside << endl;
        // cout << "empty_outside=" << empty_outside << endl;
        return filled_inside <= empty_outside;
    };

    i64 l = 0, r = k;
    while (l <= r){
        const i64 h = l + (r - l) / 2;
        if (check(h)) { r = h - 1; }
        else l = h + 1;
    }
    if (l > k) cout << -1 << endl;
    else cout << l << endl;
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
