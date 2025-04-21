// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
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

void solve(){
    i64 n, m;
    cin >> n >> m;

    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < m; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<i64> colors(n, -1);
    for (i64 s = 0; s < n; s++){
        if (colors[s] != -1) continue;
        queue<pair<i64, i64>> q;
        q.emplace(s, 0);
        while (!q.empty()){
            auto[u, c] = q.front();
            q.pop();
            if (colors[u] == c) continue; // already set
            if (colors[u] == 1 - c){
                // odd cycle!
                cout << -1 << endl;
                return;
            }
            colors[u] = c;
            for (i64 v: adj[u]){
                if (colors[v] == c){
                    // odd cycle!
                    cout << -1 << endl;
                    return;
                }
                else if (colors[v] == -1){
                    q.emplace(v, 1 - c);
                }
            }
        }
    }
    vector<i64> A, B;
    for (i64 i = 0; i < n; i++){
        if (colors[i] == 0) A.emplace_back(i);
        else B.emplace_back(i);
    }
    cout << A.size() << endl;
    for (i64 i: A) cout << i + 1 << " ";
    cout << endl;
    cout << B.size() << endl;
    for (i64 i: B) cout << i + 1 << " ";
    cout << endl;
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
