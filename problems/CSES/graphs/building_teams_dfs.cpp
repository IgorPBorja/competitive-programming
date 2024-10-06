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

const i64 N = 1e5;
vector<bool> color(N, false);
vector<bool> vis(N, false);
vector<vector<i64>> adj(N);
bool ok = true;

void dfs(i64 u, bool c = false){
    color[u] = c;
    vis[u] = true;
    for (i64 v: adj[u]){
        if (vis[v] && color[v] == color[u]){
            ok = false;
        } 
        // else if vis[v] and color[v] == !color[u]: does nothing
        else if (!vis[v]){
            color[v] = !c;
            dfs(v, !c);
        }
    }
}

void solve(){
    i64 n, m;
    cin >> n >> m;
    i64 a, b;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        --a; --b;
        adj[a].eb(b);
        adj[b].eb(a);
    }
    for (i64 i = 0; i < n; i++){
        if (!vis[i]){
            dfs(i);
        }
    }
    if (!ok){
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (i64 i = 0; i < n; i++){
            cout << (color[i] ? 1 : 2) << " ";
        }
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
