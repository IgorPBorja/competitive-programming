#define TESTCASES
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
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

const i64 W = 26;

struct DSUChains {
	array<i64, W> p, sz;
	array<bool, W> in, out;
	array<i64, W> f;
	i64 components = W;

	DSUChains() {
		fill(in.begin(), in.end(), 0);
		fill(out.begin(), out.end(), 0);
		iota(p.begin(), p.end(), 0);
		fill(sz.begin(), sz.end(), 0);
		fill(f.begin(), f.end(), W + 10);
	}

	i64 find(i64 x){
		if (p[p[x]] != p[x]){
			p[x] = find(p[x]);
		}
		return p[x];
	}

	void merge(i64 x, i64 y){
		i64 ox = x, oy = y;
		x = find(x), y = find(y);
		if (x == y) return;

		if (sz[x] > sz[y]) swap(x, y);
		p[x] = y;
		sz[y] += sz[x];

		f[ox] = oy;
		in[oy] = true;
		out[ox] = true;
		--components;
	}

	void assign(i64 x){
		if (out[x]) return;
		for (i64 i = 0; i < W; i++){
			if (components == 1 && !in[i]){
				f[x] = i;
				return;  // close cycle
			} else if (find(i) != find(x) && !in[i]){
				merge(x, i);
				return;
			}
		}
	}
};

void solve(){
	i64 n;
	cin >> n;
	string s;
	cin >> s;

	DSUChains dsu;
	for (i64 i = 0; i < n; i++){
		dsu.assign(s[i] - 'a');
	}

	string t;
	t.reserve(n);
	for (i64 i = 0; i < n; i++){
		t.push_back(dsu.f[s[i] - 'a'] + 'a');
	}
	cout << t << endl;
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
