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

struct DSU {
	vector<i64> parent, sz, lazy, val;
	vector<vector<i64>> subset;

	DSU(i64 n){
		parent.resize(n);
		sz.assign(n, 1);
		lazy.assign(n, 0);
		val.assign(n, 0);
		subset.resize(n);

		for (i64 i = 0; i < n; i++){
			parent[i] = i;
			subset[i].emplace_back(i);
		}
	}

	i64 find(i64 x){
		if (parent[x] != x){
			parent[x] = find(parent[x]); // path compression
		}
		return parent[x];
	}

	i64 get(i64 x){
		return val[x] + lazy[find(x)];
	}

	void merge(i64 x, i64 y){
		x = find(x);
		y = find(y);
		if (x == y){
			return;
		} else if (sz[x] < sz[y]) {
			swap(x, y);
		}
		for (i64 z: subset[y]){
			// commit lazy
			val[z] += lazy[y];
			// undo unwanted update from parent
			val[z] -= lazy[x];
			subset[x].emplace_back(z);
		}
		sz[x] += sz[y];
		parent[y] = x;
	}

	void add(i64 x, i64 v){
		lazy[find(x)] += v;
	}
};

void solve(){
	i64 n, m;
	cin >> n >> m;

	DSU dsu(n);
	for (i64 i = 0; i < m; i++){
		string action;
		i64 x, y, v;
		cin >> action >> x;
		--x;  // 0-indexing
		if (action == "join"){
			cin >> y;
			--y;
			dsu.merge(x, y);
		} else if (action == "add"){
			cin >> v;
			dsu.add(x, v);
		} else {
			cout << dsu.get(x) << endl;
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
