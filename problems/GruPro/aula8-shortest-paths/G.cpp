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
	i64 dist[n][n];
	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < n; j++){
			cin >> adj[i][j];
			dist[i][j] = adj[i][j];
		}
	}
	i64 x[n];  // deleted vertices, in order of deletion ==> we must reverse this
	i64 sums_post_insertion[n];
	bool added[n];
	for (i64 i = 0; i < n; i++){
		cin >> x[i];
		--x[i];
		added[i] = false;
	}
	reverse(x, x + n);

	// loop invariant: after iteration k, dist[i][j] is the distance using only vertices in [x[0], ..., x[k]] as intermediates
	// thus we want for each k the sum dist[i][j] where i and j were already added
	// since then the intermediate points AND the endpoints will be in the subgraph induced by [x[0], ..., x[k]]
	for (i64 k = 0; k < n; k++){
		added[x[k]] = true;
		sums_post_insertion[k] = 0;
		for (i64 i = 0; i < n; i++){
			for (i64 j = 0; j < n; j++){
				dist[i][j] = min(dist[i][j], dist[i][x[k]] + dist[x[k]][j]);
				if (added[i] && added[j]) sums_post_insertion[k] += dist[i][j];
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
