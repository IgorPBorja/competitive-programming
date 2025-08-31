#define TESTCASES
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

/*
make residual graph
make layer graph
find blocking flow
repeat
*/

const i64 INF = (i64)2e18;

struct EdgePair {
    i64 u, v, c, f;

    EdgePair(i64 from, i64 to, i64 cap) : u(from), v(to), c(cap), f(0) {}

    i64 cap_from(i64 from){
        if (from == u) return c - f;
        else return f;
    }

    i64 other(i64 from){
        if (from == u) return v;
        else return u;
    }

    void add_flow(i64 from, i64 df){
        if (from == u){  // forward flow, consumes capacity
            f += df;
        } else {  // backwards flow, gives back capacity
            f -= df;
        }
    }
};

struct Dinic {
    vector<vector<EdgePair*>> res;
    i64 n, s, t;

    Dinic(i64 n, i64 s, i64 t) : n(n), s(s), t(t) {
        res.resize(n);
    }

    void add_edge(i64 u, i64 v, i64 cap){
        EdgePair* e = new EdgePair(u, v, cap);
        res[u].emplace_back(e);
        res[v].emplace_back(e);
    }

    pair<vector<vector<EdgePair*>>, vector<i64>> bfs(){
        vector<i64> levels(n, INF);
        vector<vector<EdgePair*>> layered_res(n);
        queue<pair<i64, i64>> q;
        q.emplace(s, 0);
        while (!q.empty()){
            auto[u, l] = q.front();
            q.pop();
            if (l >= levels[u]) continue;
            levels[u] = l;
            for (EdgePair* e: res[u]){
                if (e->cap_from(u) == 0) continue;  // edge does not exist, no capacity
                i64 v = e->other(u);
                if (levels[v] == INF){
                    layered_res[u].emplace_back(e);
                    q.emplace(v, l + 1);
                }
            }
        }
        return {layered_res, levels};
    }

    // tries to push dF of flow
    i64 push_flow(i64 u, i64 dF, const vector<vector<EdgePair*>>& dag, vector<i64>& blocked){
        if (u == t) {
            return dF;
        }
        i64 pushedF = 0;
        bool all_neighbors_blocked = true;
        for (EdgePair* e: dag[u]){
            if (dF == 0) break;
            i64 v = e->other(u);
            if (blocked[v] || e->cap_from(u) == 0) continue;  // blocked edge
            i64 delta = push_flow(v, min(dF, e->cap_from(u)), dag, blocked);
            if (delta){
                e->add_flow(u, delta);
                dF -= delta;
                pushedF += delta;
                all_neighbors_blocked = false;
            }
        }
        if (all_neighbors_blocked) blocked[u] = true;
        return pushedF;
    }

    i64 maxflow(){
        while (true){
            vector<i64> blocked(n, false);
            auto[dag, levels] = bfs();
            if (levels[t] == INF) {  // can't push any positive flow to sink
                break;
            }
            push_flow(s, INF, dag, blocked);
        }
        i64 maxf = 0;
        for (EdgePair* e: res[s]){
            if (s == e->u){ // forward flow
                maxf += e->f;
            } else {  // backward flow
                maxf -= e->f;
            }
        }
        return maxf;
    }
};

void solve(){
    /*
    Network:
        - virtual source connects to all noise (P) nodes with capacity +INF
        - virtual sink connects to all silence (S) nodes with capacity +INF
        - real edges with weight 1

    Remove each edge has a cost of 1 (since we want the amount of edges), we can't remove the virtual edges,
    and we want to disconnect source and sink given these restrictions
    
    which is the reason real edges have cap=1 and virtual edges cap=INF.

    Since this is a unit network, it should run in O(E sqrt(V)) = O(N^{3/2})
    */
    i64 n;
    cin >> n;
    Dinic dinic(n + 2, 0, n + 1);

    vector<i64> S, P;
    for (i64 i = 2; i <= n; i++){
        i64 j;
        cin >> j;
        // i <-> j, 1-indexed
        dinic.add_edge(i, j, +1);
        dinic.add_edge(j, i, +1);
    }
    string desc;
    cin >> desc;
    for (i64 i = 1; i <= n; i++){
        if (desc[i - 1] == 'S'){
            S.emplace_back(i);
        } else if (desc[i - 1] == 'P'){
            P.emplace_back(i);
        }
    }
    for (i64 i: P){
        dinic.add_edge(0, i, +INF);
    }
    for (i64 i: S){
        dinic.add_edge(i, n + 1, +INF);
    }

    cout << dinic.maxflow() << endl;
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
