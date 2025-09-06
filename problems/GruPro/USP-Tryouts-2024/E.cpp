// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

// golden section search (i.e continuous ternary search)
// with dijkstra as check function over interval [0, T]
// Complexity: O(log(T/epsilon) * M log N)
// with M = 200, N = 100, and T=1e9 and epsilon=1e9
// Total: <= 200 * 7 * 54 = 75600

using ld = long double;

struct DSU {
    i64 n;
    vector<i64> p, sz;

    DSU(i64 n) : n(n) {
        p.resize(n);
        iota(all(p), 0);
        sz.assign(n, 1);
    }

    i64 find(i64 x){
        return (p[x] == p[p[x]] ? p[x] : p[x] = find(p[x]));
    }

    bool merge(i64 x, i64 y){
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (sz[x] > sz[y]) swap(x, y);
        // x -> y
        sz[y] += sz[x];
        p[x] = y;
        return true;
    }

    // bool is_connected(){
    //     i64 root = find(0);
    //     for (i64 i = 1; i < n; i++){
    //         if (find(i) != root) return false;
    //     }
    //     return true;
    // }
};

// cost of MST at time t and if mst is complete
ld cost(
    // u -> (a,b,c,v)
    const vector<tuple<ld, ld, ld, i64, i64>>& template_edges,
    ld t
){
    const i64 n = template_edges.size();
    vector<tuple<ld, i64, i64>> edges;
    for (auto[a,b,c,u,v]: template_edges) {
        edges.emplace_back(a * t * t + b * t + c, u, v);
    }
    DSU dsu(n);
    sort(all(edges));
    ld mst_cost = 0.0f;
    for (auto[x, u, v]: edges){
        if (dsu.merge(u, v)){
            mst_cost += x;
        }
    }
    return mst_cost;
}

// minimizing unimodal function with golden section search
ld gss(const vector<tuple<ld, ld, ld, i64, i64>>& template_edges){
    ld a = -1e9;
    ld b = +1e9;
    const ld eps = 1e-10;

    ld r = (sqrt((ld)5) - (ld)1) / ((ld)2);
    ld x1 = b - r * (b - a), x2 = a + r * (b - a);
    ld f1 = cost(template_edges, x1), f2 = cost(template_edges, x2);
    while (b - a > eps){
        if (f1 < f2){
            b = x2; x2 = x1; f2 = f1;
            x1 = b - r * (b - a); f1 = cost(template_edges, x1);
        } else {
            a = x1; x1 = x2; f1 = f2;
            x2 = a + r * (b - a); f2 = cost(template_edges, x2);
        }
    }
    return cost(template_edges, a);
}

void solve(){
    i64 n, m;
    cin >> n >> m;
    vector<tuple<ld, ld, ld, i64, i64>> edges(m);
    for (i64 i = 0; i < m; i++){
        i64 x, y;
        ld a, b, c;
        cin >> x >> y >> a >> b >> c;
        --x; --y;
        edges.emplace_back(a, b, c, x, y); 
    }
    ld min_cost = gss(edges);
    cout << fixed << setprecision(15) << min_cost << endl;
}
 
signed main(){
	fastio;
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
