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
			debug << setw(3) << (v != INF ? to_string(v) : "INF") << " "; \
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

// copied from KACTL
struct PushRelabel {
    struct Edge {
        i64 dest, back;
        i64 f, c;
    };
    vector<vector<Edge>> g;
    vector<i64> ec;
    vector<Edge*> cur;
    vector<vector<i64>> hs;
    vector<i64> H;
    PushRelabel(i64 n): g(n), ec(n), cur(n), hs(2 * n), H(n) {}

    void addEdge(i64 s, i64 t, i64 cap, i64 rcap=0){
        if (s == t) return;
        g[s].push_back({t, g[t].size(), 0, cap});
        g[t].push_back({s, g[s].size() - 1, 0, rcap});
    }

    void addFlow(Edge& e, i64 f){
        Edge& back = g[e.dest][e.back];
        if (!ec[e.dest] && f){
            hs[H[e.dest]].emplace_back(e.dest);
        }
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }

    i64 calc(i64 s, i64 t){
        i64 v = g.size(); H[s] = v; ec[t] = 1;
        vector<i64> co(2 * v); co[0] = v-1;
        for (i64 i = 0; i < v; i++){
            cur[i] = g[i].data();
        }
        for (Edge& e: g[s]) addFlow(e, e.c);

        for (i64 hi = 0;;){
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            i64 u = hs[hi].back(); hs[hi].pop_back();
            while (ec[u] > 0){
                if (cur[u] == g[u].data() + g[u].size()){
                    H[u] = (i64)1e9;
                    for (Edge& e: g[u]) {
                        if (e.c && H[u] > H[e.dest] + 1){
                            H[u] = H[e.dest] + 1, cur[u] = &e;
                        }
                    }
                    if (++co[H[u]], !--co[hi] && hi < v){
                        for (i64 i = 0; i < v; i++){
                            if (hi < H[i] && H[i] < v){
                                --co[H[i]], H[i] = v + 1;
                            }
                        }
                    }
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1){
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                } else ++cur[u];
            }
        }
    }
};

const i64 T = (i64)1e6;
const i64 INF = (i64)1e9;

void solve(){
    i64 p, r, c;
    cin >> p >> r >> c;

    vector<i64> d(p), e(r);
    for (i64 i = 0; i < p; i++) cin >> d[i];
    for (i64 i = 0; i < r; i++) cin >> e[i];
    vector<tuple<i64, i64, i64>> edges(c);  // producer of flow to consumer of flow
    for (i64 i = 0; i < c; i++){
        i64 u, v, delta;
        cin >> u >> v >> delta;
        --u; --v;
        edges[i] = make_tuple(v, u, delta);
    }
    i64 total_demand = 0;
    for (i64 i = 0; i < p; i++) total_demand += d[i];
    // NOTE graph is bipartite

    i64 lo = 1, hi = T, ans = INF;
    while (lo <= hi){
        const i64 t = lo + (hi - lo) / 2;
        // build graph
        // source is 0, sink is p+r+1
        PushRelabel ps(p + r + 2);
        // source to first partition
        for (i64 i = 0; i < r; i++){
            ps.addEdge(0, i + 1, e[i]);
        }
        // second partition to sink
        for (i64 i = 0; i < p; i++){
            // r+1..r+p
            ps.addEdge(r+1+i, r+1+p, d[i]);
        }
        for (auto[u, v, delta]: edges){
            if (delta <= t){
                ps.addEdge(u+1, r+1+v, INF);
            }
        }
        i64 flow = ps.calc(0, p+r+1);
        if (flow >= total_demand){
            ans = t;
            hi = t - 1;
        } else {
            lo = t + 1;
        }
    }
    if (ans == INF){
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
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
