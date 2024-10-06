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
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;
const i64 INF = 1e18;

// guarantee that all (u,v) edges satisfy
// d(u, src) < d(v, src) OR d(u, src) == d(v, src) and u < v
// therefore there can't be a cycle since the pairs (d(a[i], src), a[i]) are strictly increasing
vector<pair<i64, i64>> make_dag(vector<vector<i64>> &g){
	vector<pair<i64, i64>> directed_edges;
	for (i64 u = 0; u < g.size(); u++){
		for (i64 v: g[u]){
			if (u < v){
				directed_edges.emplace_back(u, v);
			}
		}
	}
	return directed_edges;
}

void solve(){
	i64 n, m;
	cin >> n >> m;

	vector<vector<i64>> g(n);
	for (i64 i = 0; i < m; i++){
		i64 a, b;
		cin >> a >> b;
		--a; --b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	vector<pair<i64, i64>> dag_edges = make_dag(g);
	for (auto[u, v]: dag_edges){
		cout << u + 1 << " " << v + 1 << endl;
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
