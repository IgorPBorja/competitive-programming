// #define TESTCASES
// #define DEBUG
 
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
	out << x.first << "," << x.second;
	return out;
}

const i64 INF = 1e9;
const i64 dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

i64 bfs01(vector<vector<i64>> &grid, pair<i64, i64> src, pair<i64, i64> dest, i64 k){
	const i64 n = grid.size(), m = grid[0].size();
	vector<vector<i64>> dist = vector<vector<i64>>(n, vector<i64>(m, INF));

	auto valid = [n, m, &grid](i64 x, i64 y){
		return 0 <= x && x < n && 0 <= y && y < m && (grid[x][y] == 1);
	};

	queue<pair<pair<i64, i64>, i64>> q;
	q.emplace(make_pair(src, 0));
	dist[src.first][src.second] = 0;
	while (!q.empty()){
		auto[u, d] = q.front();
		q.pop();
		if (u == dest){
			break;
		}
		for (i64 i = 0; i < 4; i++){
			for (i64 steps = 1; steps <= k; steps++){
				i64 x2 = u.first + steps * dx[i], y2 = u.second + steps * dy[i];
				if (!valid(x2, y2)){
					break;
				} else if (dist[x2][y2] < d + 1){
					// it is fine to stop here and start new run on x2, y2
					// NOTE: the inequality is strict since it might be that (ux + dx[i] * 3, uy + dy[i] * 3) is reachable with distance d + 1, but (ux + dx[i] * 4, uy + dy[i] * 4) is still not, so we'd want to process it
					break;
				}
				if (dist[x2][y2] == INF){
					dist[x2][y2] = d + 1;
					q.emplace(make_pair(x2, y2), d + 1);
				}
			}
		}
	}
	return dist[dest.first][dest.second];
}

void solve(){
	i64 n, m, k;
	cin >> n >> m >> k;

	string s;
	vector<vector<i64>> grid(n, vector<i64>(m));

	for (i64 i = 0; i < n; i++){
		cin >> s;
		for (i64 j = 0; j < m; j++){
			grid[i][j] = (s[j] == '.') ? 1 : 0;
		}
	}

	pair<i64, i64> src, dest;
	cin >> src.first >> src.second >> dest.first >> dest.second;
	--src.first; --src.second; --dest.first; --dest.second;
	i64 ans = bfs01(grid, src, dest, k);
	if (ans < INF){
		cout << ans << endl;
	} else {
		cout << -1 << endl;
	}
}
 
signed main(){
	fastio;
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
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
