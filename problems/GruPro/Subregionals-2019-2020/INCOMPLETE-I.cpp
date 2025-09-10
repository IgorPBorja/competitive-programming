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

const int INF = (i64)1e9;
const int MAXN = 400;

// dist[k][i][j]: i->j distance using low-k for current k
int dist_coldest[MAXN][MAXN];
// dist[k][i][j]: i->j distance using high-k for current k
int dist_hottest[MAXN][MAXN];

int idx[MAXN];  // idx of vertex i on sorted temperatures
vector<int> idxs_by_temp[MAXN];  // because of ties there might be many such indices

// (a, b, idx, mode)
vector<tuple<int, int, int, int>> queries_per_k[MAXN];

// k is 0-indexed
void update_dijkstra(i64 k, const vector<vector<pair<int, int>>>& G, const int MAX_IDX){
    for (int i = 0; i < k; i++){
        min_pq<pair<int, int>> pq;
        for (int start: idxs_by_temp[i]){  // pq is always empty at the end of this loop, so it is fine sharing it
            // just update dijkstra from this start
            for (int cold: idxs_by_temp[k]){
                // cold was never seen so dist is INF
                dist_coldest[start][cold] = INF;
                for (auto[w, v]: G[cold]){  // graph is undirected
                    // v->cold edge where v is valid from last k value (hence >=)
                    if (idx[v] >= k) continue;
                    pq.emplace(dist_coldest[start][v] + w, cold);
                }
            }
            while (!pq.empty()){
                auto[d, u] = pq.top();
                pq.pop();
                if (d >= dist_coldest[start][u]) continue;
                dist_coldest[start][u] = d;
                for (auto[w, v]: G[u]){
                    if (idx[v] > k) continue;
                    if (d + w < dist_coldest[start][v]){
                        pq.emplace(d + w, v);  // adding cold relaxed this edge
                    }
                }
            }
        }
        // now pq is clear, do hot update
        for (int start: idxs_by_temp[MAX_IDX - i]){  // pq is always empty at the end of this loop, so it is fine sharing it
            for (int hot: idxs_by_temp[MAX_IDX - k]){
                dist_hottest[start][hot] = INF;
                for (auto[w, v]: G[hot]) {  // graph is undirected
                    // v->hot edge where v is valid from last k value
                    if (idx[v] <= MAX_IDX - k) continue;
                    pq.emplace(dist_hottest[start][v] + w, hot);
                }
            }
            while (!pq.empty()){
                auto[d, u] = pq.top();
                pq.pop();
                if (d >= dist_hottest[start][u]) continue;
                dist_hottest[start][u] = d;
                for (auto[w, v]: G[u]){
                    if (idx[v] < MAX_IDX - k) continue;
                    if (d + w < dist_hottest[start][v]){
                        pq.emplace(d + w, v);  // adding cold relaxed this edge
                    }
                }
            }
        }
    }

    // new dijkstras for new vertices
    min_pq<pair<int, int>> pq;
    for (int cold: idxs_by_temp[k]){
        for (int i = 0; i <= k; i++) {
            for (int u: idxs_by_temp[i]) dist_coldest[cold][u] = INF;
        }
        pq.emplace(0, cold);
        while (!pq.empty()){
            auto[d, u] = pq.top();
            pq.pop();
            if (d >= dist_coldest[cold][u]) continue;
            dist_coldest[cold][u] = d;
            for (auto[w, v]: G[u]){
                if (idx[v] > k) continue;
                if (d + w < dist_coldest[cold][v]){
                    pq.emplace(d + w, v);
                }
            }
        }
    }

    for (int hot: idxs_by_temp[MAX_IDX - k]){
        for (int i = 0; i <= k; i++) {
            for (int u: idxs_by_temp[MAX_IDX - i]) dist_hottest[hot][u] = INF;
        }
        pq.emplace(0, hot);
        while (!pq.empty()){
            auto[d, u] = pq.top();
            pq.pop();
            if (d >= dist_hottest[hot][u]) continue;
            dist_hottest[hot][u] = d;
            for (auto[w, v]: G[u]){
                if (idx[v] < MAX_IDX - k) continue;
                if (d + w < dist_hottest[hot][v]){
                    pq.emplace(d + w, v);
                }
            }
        }
    }
}

int answer_query(
    int a, int b, int k,   // k is 0-indexed
    const vector<vector<pair<int, int>>>& G,
    const bool is_cold,
    const int MAX_IDX
){
    int ans = INF;
    for (auto[wa, c]: G[a]){
        if (c == b) ans = min(ans, wa);  // direct edge between a,b without intermediaries
        if ((is_cold && idx[c] > k) || (!is_cold && idx[c] < MAX_IDX - k)) continue;  // can't use this edge
        for (auto[wb, d]: G[b]){  // d->b edge (graph is undirected)
            if ((is_cold && idx[d] > k) || (!is_cold && idx[d] < MAX_IDX - k)) continue;  // can't use this edge
            if (is_cold){
                ans = min(ans, wa + dist_coldest[c][d] + wb);
            } else {
                ans = min(ans, wa + dist_hottest[c][d] + wb);
            }
        }
    }
    return ans;
}

void solve(){
    int n, r;
    cin >> n >> r;
    vector<pair<int, int>> t(n);
    for (int i = 0; i < n; i++){
        cin >> t[i].first;
        t[i].second = i;
    }
    vector<vector<pair<int, int>>> G(n);
    for (int i = 0; i < r; i++){
        int x, y, d;
        cin >> x >> y >> d;
        --x; --y;
        G[x].emplace_back(d, y);
        G[y].emplace_back(d, x);
        /*
        Graph is undirected. For e.g this test case
        5 5
        1 1 1 2 2
        1 2 100
        2 3 100
        3 4 1
        4 5 1
        5 1 100
        3
        1 3 1 0
        1 3 2 0
        1 3 1 1

        expects answers 200, 102, 102
        */
    }
    // cerr << "graph ok" << endl;

    sort(all(t));
    int max_idx = 0;
    idx[t[0].second] = 0;
    idxs_by_temp[0].emplace_back(t[0].second);
    for (int i = 1; i < n; i++){
        auto[t_prev, prev] = t[i - 1];
        auto[t_cur, cur] = t[i];  // node cur is the i-th smallest temp (i being 0 indexed)
        if (t_cur > t_prev) ++max_idx;
        idx[cur] = max_idx;
        idxs_by_temp[max_idx].emplace_back(cur);
    }

    // cerr << "indices ok" << endl;

    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        int a, b, k, t;
        cin >> a >> b >> k >> t;
        --a; --b;
        --k;  // 0-index k
        queries_per_k[k].emplace_back(a, b, i, t);
    }

    // cerr << "initial build ok" << endl;

    vector<int> ans(q);

    // #define prn_cold cerr << "COLD DIST=" << endl; \
    //     for (int i = 0; i < n; i++) { \
    //         for (int j = 0; j < n; j++) { \
    //             if (idx[i] > k || idx[j] > k || dist_coldest[i][j] == INF) cerr << "INF" << " "; \
    //             else cerr << setw(3) << dist_coldest[i][j] << " "; \
    //         } \
    //         cerr << endl; \
    //     }
    // #define prn_hot cerr << "HOT DIST=" << endl; \
    //     for (int i = 0; i < n; i++) { \
    //         for (int j = 0; j < n; j++) { \
    //             if (idx[i] < n - 1 - k || idx[j] < n - 1 -k || dist_coldest[i][j] == INF) cerr << "INF" << " "; \
    //             else cerr << setw(3) << dist_hottest[i][j] << " "; \
    //         } \
    //         cerr << endl; \
    //     }

    for (int k = 0; k <= max_idx; k++){
        update_dijkstra(k, G, max_idx);
        // cerr << "-------------at k=" << k << "-----------------------" << endl;
        // prn_cold;
        // prn_hot;
        // cerr << "updated_dijkstra for k=" << k << endl;
        for (auto[a, b, i, is_hot]: queries_per_k[k]){
            ans[i] = answer_query(a, b, k, G, !is_hot, max_idx);  // we take is_cold, not is_hot
        }
        // cerr << "answered all queries for k=" << k << endl;
    }
    for (int i = 0; i < q; i++){
        cout << (ans[i] == INF ? -1 : ans[i]) << " ";
    }
    cout << endl;
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
