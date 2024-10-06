#define TESTCASES
 
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

bool valid(i64 x, i64 y, i64 n, i64 m = 2){
	return (0 <= x) && (x < m) && (0 <= y) && (y < n);
}

void solve(){
	i64 n;
	cin >> n;
	bool vis[2][n];

	i64 dir[2][n];
	char c;
	for (i64 i = 0; i < 2; i++){
		for (i64 j = 0; j < n; j++){
			cin >> c;
			if (c == '>'){
				dir[i][j] = 1;
			} else {
				dir[i][j] = -1;
			}
			vis[i][j] = false;
		}
	}

	vector<pair<i64, i64>> adj[2][n];
	for (i64 i = 0; i < 2; i++){
		for (i64 j = 0; j < n; j++){
			i64 dx[4] = {-1,1,0,0}, dy[4] = {0,0,-1,1};
			for (i64 k = 0; k < 4; k++){
				if (!valid(i + dx[k], j + dy[k], n)) continue;
				adj[i][j].emplace_back(i + dx[k], j + dy[k] + dir[i + dx[k]][j + dy[k]]);
			}
		}
	}

	queue<pair<i64, i64>> q;
	q.emplace(make_pair(0, 0));
	while (!q.empty()){
		auto[x, y] = q.front();
		q.pop();
		if (vis[x][y]) continue;
		vis[x][y] = true;
		for (auto[w, z]: adj[x][y]){
			if (!vis[w][z]){
				q.emplace(make_pair(w, z));
			}
		}
	}
	if (vis[1][n - 1]){
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
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

