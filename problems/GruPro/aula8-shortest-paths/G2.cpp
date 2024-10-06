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

const i64 INF = 1e16;

void solve(){
	i64 n;
	cin >> n;

	i64 adj[n][n];
	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < n; j++){
			cin >> adj[i][j];
		}
	}
	i64 dist[n][n];
	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < n; j++){
			dist[i][j] = INF;
		}
	}

	i64 x[n];  // deleted vertices, in order of deletion ==> we must reverse this
	i64 sums_post_insertion[n];
	for (i64 i = 0; i < n; i++){
		cin >> x[i];
		--x[i];
	}
	reverse(x, x + n);

	vector<i64> vertices;
	// O(N^3)
	for (i64 i = 0; i < n; i++){
		// update all distances with the new edges
		// dist'[i][j] = min(dist[i][i'] + adj[i'][x[k]]) + min(adj[x[k]][j'] + dist[j'][j])
		dist[x[i]][x[i]] = 0;

		// does not include x[i] yet
		i64 first_half[n], second_half[n];
		for (i64 u: vertices){
			first_half[u] = adj[u][x[i]];
			second_half[u] = adj[x[i]][u];
			for (i64 v: vertices){
				first_half[u] = min(first_half[u], dist[u][v] + adj[v][x[i]]);
				second_half[u] = min(second_half[u], adj[x[i]][v] + dist[v][u]);
			}
		}
		first_half[x[i]] = 0; second_half[x[i]] = 0;

		// now include x[i]
		vertices.emplace_back(x[i]);	
		sums_post_insertion[i] = 0;
		for (i64 u: vertices){
			for (i64 v: vertices){
				dist[u][v] = min(dist[u][v], first_half[u] + second_half[v]);	
				sums_post_insertion[i] += dist[u][v];
			}
		}
	}

	for (i64 i = n - 1; i >= 0; i--){
		cout << sums_post_insertion[i] << " ";
	}
	cout << endl;
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
