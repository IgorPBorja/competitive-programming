//#define TESTCASES
 
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

const i64 INF = 2e18;
const i64 MAXN = 2e3;
i64 n, m, w;

bool valid(i64 x, i64 y){
    return (0 <= x && x < n && 0 <= y && y < m);
}

vector<vector<i64>> grid(MAXN, vector<i64>(MAXN));
vector<vector<i64>> src_dist(MAXN, vector<i64>(MAXN, INF));
vector<vector<i64>> dest_dist(MAXN, vector<i64>(MAXN, INF));
// vector<vector<pair<i64, i64>>> components;  // vector of component positions
vector<pair<i64, i64>> src_portals; // vector of portals in src components
vector<pair<i64, i64>> dest_portals; // vector of portals per component

/*
ans = min(
    dist(source, dest),
    min(dist(p) + cost(p) for p portal in component of source) 
        + min(dist(p) + cost(p) for p portal in component of dest) 
)
*/

void bfs(
    i64 start_x, 
    i64 start_y, 
    vector<vector<i64>>& dist_matrix, 
    vector<pair<i64, i64>>& portal_list
){
    queue<pair<pair<i64, i64>, i64>> q;
    q.emplace(make_pair(start_x, start_y), 0);
    i64 dx[4] = {-1, 1, 0, 0};
    i64 dy[4] = {0, 0, -1, 1};
    while (!q.empty()){
        auto [v, dv] = q.front();
        auto [vx, vy] = v;
        q.pop();
        if (dist_matrix[vx][vy] != INF){
            continue;
        }
        // seeing it for the first time
        dist_matrix[vx][vy] = dv;
        if (grid[vx][vy] > 0){
            // portal
            portal_list.eb(vx, vy);
        }
        for (i64 k = 0; k < 4; k++){
            if (valid(vx + dx[k], vy + dy[k]) 
                && grid[vx + dx[k]][vy + dy[k]] != -1
                && dist_matrix[vx + dx[k]][vy + dy[k]] == INF
            ){
                q.emplace(make_pair(vx + dx[k], vy + dy[k]), dv + w);
            }
        }
    }
}

void solve(){
    cin >> n >> m >> w;

    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            cin >> grid[i][j];
        }
    }


    bfs(0, 0, src_dist, src_portals);
    bfs(n - 1, m - 1, dest_dist, dest_portals);
    
    i64 ans = src_dist[n - 1][m - 1];
    i64 min_src_portals = INF, min_dest_portals = INF;
    for (auto[px, py]: src_portals){
        min_src_portals = min(min_src_portals, src_dist[px][py] + grid[px][py]);
    }
    for (auto[px, py]: dest_portals){
        min_dest_portals = min(min_dest_portals, dest_dist[px][py] + grid[px][py]);
    }
    ans = min(ans, min_src_portals + min_dest_portals);

    if (ans < INF){
        cout << ans << endl;
    } else {
        cout << -1 << endl;
    }
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
