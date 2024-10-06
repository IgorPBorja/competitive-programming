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

const i64 INF = 1e18;  // to assure 2 * INF does not overflow, which is crucial 
// if there is a u-v edge where u is isolated from both 1 and n

vector<i64> dijkstra(const vector<vector<pair<i64, i64>>> &graph, i64 s){
    priority_queue<pair<i64, i64>, vector<pair<i64, i64>>, greater<pair<i64, i64>>> min_pq;
    vector<i64> dist(graph.size(), INF);
    min_pq.emplace(0, s);
    while (!min_pq.empty()){
        auto [d, u] = min_pq.top();
        min_pq.pop();
        if (d >= dist[u]){
            continue;
        }
        dist[u] = d;
        // improve stuff
        for (auto[delta, v]: graph[u]){
            if (dist[u] + delta < dist[v]){
                min_pq.emplace(dist[u] + delta, v);
            }
        }
    }
    return dist;
}

void solve(){
    i64 n, m;
    cin >> n >> m;

    vector<vector<pair<i64, i64>>> graph(n);
    vector<vector<pair<i64, i64>>> rev_graph(n);
    i64 a, b, c;
    for (i64 i = 0; i < m; i++){
        cin >> a >> b >> c;
        --a; --b;
        graph[a].emplace_back(c, b);
        rev_graph[b].emplace_back(c, a);
    }

    vector<i64> src_dist = dijkstra(graph, 0), dest_dist = dijkstra(rev_graph, n - 1);
    // print(src_dist);
    // print(dest_dist);
    i64 min_route = INF;
    // case 1: discounted edge is in the middle
    for (i64 u = 0; u < n; u++){
        for (auto[d, v]: graph[u]){
            min_route = min(src_dist[u] + d / 2 + dest_dist[v], min_route);
        }
    }
    // case 2: discounted edge is the first
    for (auto[d, u]: graph[0]){
        min_route = min(d / 2 + dest_dist[u], min_route);
    }
    // case 3: discounted edge is the last
    for (auto[d, u]: rev_graph[n - 1]){
        min_route = min(d / 2 + src_dist[u], min_route);
    }
    cout << min_route << endl;
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
