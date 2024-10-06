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
const i64 INF = 2e18;

struct DSU {
	vector<i64> p, sz, first;
	const i64 root = 0;
	vector<vector<i64>> components;

	DSU(i64 n){
		p.resize(n);
		iota(p.begin(), p.end(), 0);
		sz.assign(n, 1);
		first.assign(n, INF);
		components.resize(n);
		for (i64 i = 0; i < n; i++) components[i].emplace_back(i);
	}

	i64 find(i64 x){
		if (p[x] != x) p[x] = find(p[x]);
		return p[x];
	}
	
	void merge(i64 x, i64 y, i64 time=0, bool should_register=false){
		x = find(x), y = find(y);	
		if (x == y) return;
		if (sz[x] > sz[y]) swap(x, y);	

		if (should_register){
			if (x == find(root)){
				for (i64 u: components[y]) first[u] = time;
			} else if (y == find(root)){
				for (i64 u: components[x]) first[u] = time;
			}
		}
		
		sz[y] += sz[x];
		p[x] = y;
		for (i64 u: components[x]){
			components[y].emplace_back(u);
		}
	}

	// void printDSU(){
	// 	for (i64 i = 0, j = 0; i < components.size(); i++, j += (p[i] == i)){
	// 		if (p[i] == i){
	// 			printmsg("component " << j << "=", components[i].begin(), components[i].end());
	// 		}
	// 	}
	// }
};

template<typename T>
bool find_with_bsearch(T* first, T* last, T val, int count = 1){
	T* it = lower_bound(first, last, val);
	bool res = it != last;
	for (int i = 0; (i < count) && res; i++){
		res &= (*it == val);
		++it;
	}
	return res;
}

void solve(){
	i64 n, m;
	cin >> n >> m;

	i64 hands[n][2];

	for (i64 i = 0; i < n; i++){
		i64 l_i, r_i;
		cin >> l_i >> r_i;
		--l_i; --r_i;
		hands[i][0] = l_i;
		hands[i][1] = r_i;
	}

	// always i->l_i or i->r_i
	pair<i64, i64> release_edges[m];
	pair<i64, i64> orig_release[m];
	for (i64 i = 0; i < m; i++){
		i64 p, h;
		cin >> p >> h;
		--p; --h;
		release_edges[i] = {p, hands[p][h]};
	}
	copy(release_edges, release_edges + m, orig_release);
	sort(release_edges, release_edges + m);

	DSU d(n);
	// mount base DSU
	for (i64 i = 0; i < n; i++){
		if (hands[i][0] == hands[i][1] && hands[i][0] >= 0){
			i64 j = hands[i][0];
			bool released = find_with_bsearch(release_edges, release_edges + m, {i, j}, 2);
			if (!released){
				d.merge(i, j);
			}
		}
		else {
			for (i64 j = 0; j < 2; j++){
				if (hands[i][j] < 0) continue;
				bool released = find_with_bsearch(release_edges, release_edges + m, {i, hands[i][j]});
				if (!released){
					d.merge(i, hands[i][j]);
				}
			}
		}
	}

	// d.printDSU();
	for (i64 t = m - 1; t >= 0; t--){
		auto[x, y] = orig_release[t];
		// cout << "merging " << x + 1 << "->" << y + 1 << endl;
		d.merge(x, y, t, true);
		// d.printDSU();
	}

	for (i64 i = 0; i < n; i++){
		cout << ((d.first[i] == INF) ? -1 : d.first[i]) << endl;
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
