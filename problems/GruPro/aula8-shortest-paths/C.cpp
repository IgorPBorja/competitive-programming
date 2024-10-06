// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
#include <cassert>
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

vector<i64>
dijkstra(vector<vector<pair<i64, i64>>> &g, i64 src){
	vector<i64> dist(g.size(), INF);
	set<pair<i64, i64>> q;
	q.emplace(0, src);
	dist[src] = 0;
	while (!q.empty()){
		auto[d, u] = *q.begin();
		q.erase(q.begin());
		for (auto[v, w]: g[u]){
			if (dist[u] + w < dist[v]){
				q.erase(make_pair(dist[v], v));
				dist[v] = dist[u] + w;
				q.emplace(dist[v], v);
			}
		}
	}
	return dist;
}

void solve(){
	i64 n, m, s, t;
	cin >> n >> m >> s >> t;
	--s; --t;

	vector<vector<pair<i64, i64>>> g(n), rev_g(n);
	vector<tuple<i64, i64, i64>> edges;
	for (i64 i = 0; i < m; i++){
		i64 a, b, w;
		cin >> a >> b >> w;
		--a; --b;
		edges.emplace_back(a, b, w);
		g[a].emplace_back(b, w);
		rev_g[b].emplace_back(a, w);
	}
	vector<i64> dist_from_src = dijkstra(g, s);
	vector<i64> dist_to_dest = dijkstra(rev_g, t);


	//build shortest path graph
	//represent shortest path as an interval [0...D] = [d(s), d(u1)] -> [d(u1), d(u2)] -> ... -> [d(u[k - 1]), d(u[k])] -> [d(u[k]), d(t)]
	//then edge (u,v) in the shortest path graph must be on all shortest paths if there is
	//no alternative cover for its subsegment. It suffices to not exist any intersection (desconsidering endpoints)
	//since a [l, r] intersecting subsegment implies an alternative edge on the shortest path graph which implies a shortest path
	
	// build union of shortests paths
	i64 optimal = dist_from_src[t];
	vector<vector<i64>> shortest_path_graph(n);
	for (i64 u = 0; u < n; u++){
		for (auto[v, w]: g[u]){
			if (dist_from_src[u] + w + dist_to_dest[v] == optimal){
				shortest_path_graph[u].emplace_back(v);
			}
		}
	}

	vector<pair<i64, i64>> intervals;
	for (i64 u = 0; u < n; u++){
		for (i64 v: shortest_path_graph[u]){
			intervals.emplace_back(dist_from_src[u], dist_from_src[v]);
		}
	}
	sort(intervals.begin(), intervals.end(), [](pair<i64, i64> i1, pair<i64, i64> i2){
		return (i1.first < i2.first) || ((i1.first == i2.first) && i1.second > i2.second);
	});
	vector<i64> starts, ends;
	for (pair<i64, i64> i: intervals){
		starts.emplace_back(i.first);
		ends.emplace_back(i.second);
	}
	vector<i64> prefix_max_end_distance(intervals.size() + 1);
	prefix_max_end_distance[0] = -INF;
	for (i64 i = 0; i < intervals.size(); i++){
		prefix_max_end_distance[i + 1] = max(prefix_max_end_distance[i], intervals[i].second);
	}
	vector<bool> always_used(m, false);
	for (i64 i = 0; i < m; i++){
		auto[u, v, w] = edges[i];
		if (dist_from_src[u] + w + dist_to_dest[v] == optimal){
			pair<i64, i64> cur_range = make_pair(dist_from_src[u], dist_from_src[v]);
			// first ocurrence of range
			i64 pos = lower_bound(intervals.begin(), intervals.end(), cur_range) - intervals.begin();
			// between -1 and pos - 1
			i64 l = upper_bound(starts.begin(), starts.begin() + pos, cur_range.first) - starts.begin() - 1;
			// between 0 and size - 1 (last ocurrence of start <= end of p - 1)
			// note r >= pos, which explains this
			i64 r = lower_bound(starts.begin(), starts.end(), cur_range.second) - starts.begin() - 1;
			bool right_intersect = (r != pos); // there is someone which starts before (end of p) - 1 ==> free intersection
			bool left_intersect = (prefix_max_end_distance[l + 1] > cur_range.first);
			always_used[i] = !left_intersect && !right_intersect;
		}
	}
	
	// printmsg("dist from src=", dist_from_src.begin(), dist_from_src.end());
	// printmsg("dist to dest=", dist_to_dest.begin(), dist_to_dest.end());
	// printmsg("intervals=", intervals.begin(), intervals.end());
	// printmsg("end distances=", prefix_max_end_distance.begin(), prefix_max_end_distance.end());
	// printmsg("always used=", always_used.begin(), always_used.end());

	for (i64 i = 0; i < m; i++){
		auto[u, v, w] = edges[i];
		if (dist_from_src[u] == INF || dist_to_dest[v] == INF){
			cout << "NO" << endl;
		} else {
			i64 d = dist_from_src[u] + w + dist_to_dest[v];
			// we must have that all minimal paths use this edge
			// i.e all paths are of the form (s -> ... -> u -> v -> ... -> t)
			// which means (u,v) is an edge that when removed disconnects s and t in the graph of the UNIONS of all shortest paths
			if (d == optimal && always_used[i]){
				cout << "YES" << endl;
			} else if (d - optimal + 1 < w){
				// we must bring d strictly lower than minimum to make this path mandatory, since there is a unrelated minimum path
				cout << "CAN " << d - optimal + 1 << endl;
			} else {
				cout << "NO" << endl;
			}
		}
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
