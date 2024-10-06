// #define TESTCASES
// #define DEBUG
 
#include <array>
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

template <typename T, size_t sz>
ostream& operator<< (ostream& out, array<T, sz> x)
{
	out << x[0];
	for (size_t i = 1; i < sz; i++){
		out << ", " << x[i];
	}
	return out;
}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

const i64 INF = 2e18;

// NOTE: it is a undirected functional graph (max deg <= 2): either a loop or a line
// for each component one color has always one more or they are the same ==> take vertex from loop with the color that appears the most

array<i64, 2> bipartite(const vector<vector<i64>> &g, i64 u, vector<i64> &colors){
	queue<pair<i64, i64>> q;
	q.emplace(u, 0);
	i64 sz = 0;
	bool odd_cycle = false;
	while (!q.empty()){
		auto[v, c] = q.front();
		q.pop();
		if (colors[v] != -1) continue;
		colors[v] = c;
		++sz;
		for (i64 w: g[v]){
			if (colors[w] == -1){
				q.emplace(w, 1 - c);
			} else if (colors[w] == colors[v]){
				odd_cycle = true;
			}
		}
	}
	if (odd_cycle) {  // odd cycle => remove from largest
		return {sz / 2, sz / 2};
	} else {
		return {sz / 2, (sz + 1) / 2};
	}
}

void solve(){
	i64 n, m;
	i64 a, b;
	cin >> n >> m;
	vector<bool> can_sum(n + 1, false); // if there is some partition where the blues can sum up to n
	can_sum[0] = true;
	vector<vector<i64>> g(n);
	
	for (i64 i = 0; i < m; i++){
		cin >> a >> b;
		--a; --b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}

	vector<i64> colors(n, -1);
	vector<array<i64, 2>> cmps;
	// maximum num of players after breaking cycles
	i64 max_vertices = 0;
	for (i64 i = 0; i < n; i++){
		if (colors[i] == -1){
			cmps.emplace_back(bipartite(g, i, colors));
			max_vertices += cmps.back()[0] + cmps.back()[1];
		}
	}

	for (array<i64, 2> a: cmps){
		vector<bool> new_sums(n + 1, false);
		// choose first as blue
		for (i64 x = 0; x + a[0] <= n; x++){
			new_sums[x + a[0]] = can_sum[x] || new_sums[x + a[0]];
		}
		// choose second as blue
		for (i64 x = 0; x + a[1] <= n; x++){
			new_sums[x + a[1]] = can_sum[x] || new_sums[x + a[1]];
		}
		can_sum = new_sums;
	}
	for (i64 half = max_vertices / 2; half >= 0; half--){
		if (can_sum[half]){
			cout << n - 2 * half << endl;
			return;
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
