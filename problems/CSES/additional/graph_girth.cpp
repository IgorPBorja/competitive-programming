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
	out << x.first << " " << x.second;
	return out;
}

const i64 INF = 2e18;

i64 find_girth(vector<vector<i64>> &G){ // O(N + M)
	// to avoid considering the case u -> ... -> w -> v (where the vw edge is inside the uv path, in which case this is NOT a cycle)
	// we do premature setting of dist (before placing in the queue, not when reading from the queue)
	// and we do the girth minimization inside the BFS for loop
	// when in a vertex v and looking at edges vw such that d[w] == d[v] or d[w] == d[v] + 1
	// (since d[w] > d[v] means d[w] = INF, as w was not found yet, and d[w] < d[v] might mean
	// the case we try to avoid)
	// If d[v] == d[w], u is the middle of an odd cycle
	// If d[v] == d[w] - 1, w was added to the queue when a other d[v]-level node was processed before.
	//
	// Proof that every cycle will be evaluated: let C be an (v,w) cycle with center (approximate) u. In case the cycle is odd, this is trivial: when we process either v or w all (d[v]=d[w])-level nodes will be in the queue. Else, if the cycle is even, and d[v] = d[w] - 1, then if v is processed before the w-neighbor with distance d[v], and the cycle is skipped, it will be catched when we consider the other (approximate) center u' such that d'[v] - 1 = d'[w]
	const i64 n = G.size();
	i64 girth = INF;

	for (i64 u = 0; u < n; u++){
		queue<i64> q;
		vector<i64> d(G.size(), INF);
		d[u] = 0;
		q.emplace(u);
		while (!q.empty()){
			i64 v = q.front();
			q.pop();
			for (i64 w: G[v]){
				// printf("bfs src=%li, from v=%li looking at w=%li with d[v]=%li and d[w]=%li\n", u, v, w, d[v], d[w]);
				if (d[w] == INF){  // undiscovered
					d[w] = d[v] + 1;
					q.emplace(w);
				} else if ((d[w] == d[v]) || (d[w] == d[v] + 1)){
					girth = min(girth, d[w] + d[v] + 1);
				}
			}
		}
	}
	return girth;
}

void solve(){
	i64 n, m;
	cin >> n >> m;

	vector<vector<i64>> G(n);
	i64 a, b;
	for (i64 i = 0; i < m; i++){
		cin >> a >> b;
		--a; --b;
		G[a].emplace_back(b);
		G[b].emplace_back(a);
	}

	i64 girth = find_girth(G);
	if (girth < INF){
		cout << girth << endl;
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
