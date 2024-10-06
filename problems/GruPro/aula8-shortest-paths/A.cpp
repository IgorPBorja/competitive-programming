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

struct Node {
	i64 d, u, parent;
	Node(i64 d, i64 u, i64 parent) : d(d), u(u), parent(parent) {}
};

bool operator>(Node n1, Node n2){
	return n1.d > n2.d;
}

template<typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;

const i64 INF = 1e15;

vector<i64> dijkstra(vector<vector<pair<i64, i64>>> &g, i64 src) {
	vector<i64> dist(g.size(), INF);
	vector<i64> parent(g.size(), -1);
	min_pq<Node> q;
	q.emplace(0, src, -1);
	while (!q.empty()){
		auto[d, u, p] = q.top();
		q.pop();
		if (d >= dist[u]){
			// suboptimal
			continue;
		}
		dist[u] = d;
		parent[u] = p;
		for (auto[v, w]: g[u]){
			if (dist[u] + w < dist[v]){
				q.emplace(dist[u] + w, v, u);
			}
		}
	}
	return parent;
}

void solve(){
	i64 n, m;
	cin >> n >> m;

	vector<vector<pair<i64, i64>>> g(n);

	for (i64 i = 0; i < m; i++){
		i64 a, b, w;
		cin >> a >> b >> w;
		--a; --b;
		g[a].emplace_back(b, w);
		g[b].emplace_back(a, w);
	} vector<i64> parent = dijkstra(g, 0);

	i64 cur = n - 1;
	vector<i64> path;
	while (cur != -1){
		path.emplace_back(cur);
		cur = parent[cur];
	}
	reverse(path.begin(), path.end());
	if (path[0] == 0){
		for (i64 x: path){
			cout << x + 1 << " ";
		}
		cout << endl;
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
