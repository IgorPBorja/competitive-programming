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
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

const i64 INF = 1e18;

void solve(){
    i64 n, m;
    cin >> n >> m;

    vector<tuple<i64, i64, i64>> edges(m);
    for (i64 i = 0; i < m; i++){
        i64 a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        edges[i] = {a, b, c};
    }

    // virtual vertex connects to all others with weight 0
    // so ALL negative cycles are reachable!
    // for that effect we just need to set d[u] = 0 for all u
    // (we don't need an actual new vertex)
    vector<i64> d(n, 0);
    vector<i64> source_list;
    vector<i64> prev(n, -1);
    // all paths of size s
    for (i64 s = 0; s <= n; s++){
        bool any = false;
        for (auto[a, b, c]: edges){
            if (d[a] + c < d[b]){
                any = true;
                prev[b] = a;
                d[b] = d[a] + c;
            }
        }
        if (!any) break;
    }

    // run a (single) new iteration of relaxation
    i64 target = -1;
    for (auto[a, b, c]: edges){
        if (d[a] + c < d[b]){
            target = b;
            break;
        }
    }
    if (target != -1){
        cout << "YES" << endl;
        vector<i64> cyc;
        // might be a cycle end or a vertex reachable from a negative cycle
        i64 curr = target;
        vector<bool> vis(n);
        while (!vis[curr]) {
            cyc.emplace_back(curr);
            vis[curr] = true;
            // we might have prev[curr] == curr
            // (in case of self negative edges!)
            curr = prev[curr];
        }
        // now curr is a visited vertex (closed the cycle!)
        cyc.emplace_back(curr);
        reverse(cyc.begin(), cyc.end());
        while (cyc.back() != cyc[0]){
            cyc.pop_back(); // remove vertices reachable from the cycle but not in it
        }
        for (auto x: cyc){
            cout << x + 1 << " ";
        }
        cout << endl;
        return;
    }
    cout << "NO" << endl;
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
