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
            if (v == INF) debug << "INF" << " "; \
            else debug << setw(3) << v << " "; \
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


void solve(){
    i64 n, r;
    cin >> n >> r;
    vector<pair<i64, i64>> t(n);
    vector<vector<i64>> dist_coldest(n, vector<i64>(n, INF));
    vector<vector<i64>> dist_hottest(n, vector<i64>(n, INF));

    // vector<i64> idx(n);  // idx of vertex i on sorted temperatures
    vector<vector<i64>> idxs_by_temp(n);  // because of ties there might be many such indices

    // (a, b, idx)
    vector<tuple<i64, i64, i64>> queries_per_k_and_mode[2][MAXN];

    for (i64 i = 0; i < n; i++){
        cin >> t[i].first;
        t[i].second = i;
    }
    vector<vector<pair<i64, i64>>> G(n);
    for (i64 i = 0; i < r; i++){
        i64 x, y, d;
        cin >> x >> y >> d;
        --x; --y;
        G[x].emplace_back(d, y);
        G[y].emplace_back(d, x);
        dist_coldest[x][y] = dist_coldest[y][x] = 
            dist_hottest[x][y] = dist_hottest[y][x] = d;
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
    for (i64 i = 0; i < n; i++) {
        dist_coldest[i][i] = dist_hottest[i][i] = 0;
    }
    // cerr << "graph ok" << endl;

    sort(all(t));
    i64 max_idx = 0;
    // idx[t[0].second] = 0;
    idxs_by_temp[0].emplace_back(t[0].second);
    for (i64 i = 1; i < n; i++){
        auto[t_prev, prev] = t[i - 1];
        auto[t_cur, cur] = t[i];  // node cur is the i-th smallest temp (i being 0 indexed)
        if (t_cur > t_prev) ++max_idx;
        // idx[cur] = max_idx;
        idxs_by_temp[max_idx].emplace_back(cur);
    }

    i64 q;
    cin >> q;
    for (i64 i = 0; i < q; i++){
        i64 a, b, k, t;
        cin >> a >> b >> k >> t;
        --a; --b;
        --k;  // 0-index k
        k = min(k, max_idx);  // if k > max_idx, then can use all edges
        // (using k itself will result in the query not being picked up)
        queries_per_k_and_mode[t][k].emplace_back(a, b, i);
    }

    // cerr << "initial build ok" << endl;

    vector<i64> ans(q);

    for (i64 T = 0; T <= max_idx; T++){
        for (i64 k: idxs_by_temp[T]){
            for (i64 i = 0; i < n; i++){
                for (i64 j = 0; j < n; j++){
                    if (dist_coldest[i][k] != INF && dist_coldest[k][j] != INF){
                        dist_coldest[i][j] = min(dist_coldest[i][j], dist_coldest[i][k] + dist_coldest[k][j]);
                    }
                }
            }
        }
        for (auto[a, b, idx]: queries_per_k_and_mode[0][T]){
            ans[idx] = dist_coldest[a][b];
        }
    }
    for (i64 TR = 0; TR <= max_idx; TR++){
        for (i64 k: idxs_by_temp[max_idx - TR]){
            for (i64 i = 0; i < n; i++){
                for (i64 j = 0; j < n; j++){
                    if (dist_hottest[i][k] != INF && dist_hottest[k][j] != INF){
                        dist_hottest[i][j] = min(dist_hottest[i][j], dist_hottest[i][k] + dist_hottest[k][j]);
                    }
                }
            }
        }
        for (auto[a, b, idx]: queries_per_k_and_mode[1][TR]){
            ans[idx] = dist_hottest[a][b];
        }
    }
    for (i64 i = 0; i < q; i++){
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
