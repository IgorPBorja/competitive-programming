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

void solve(){
    i64 n;
    cin >> n;
    pair<i64, i64> a[n];
    i64 c[n], f[n], s[n];
    memset(f, 0, sizeof f);
    memset(s, 0, sizeof s);
    memset(c, 0, sizeof c);
    vector<vector<i64>> d(n);

    for (i64 i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
        --a[i].first; --a[i].second;
        ++c[a[i].first];
        ++c[a[i].second];
        d[a[i].first].emplace_back(i);
        d[a[i].second].emplace_back(i);
    }
    for (i64 i = 0; i < n; i++){
        if (a[i].first == a[i].second){
            cout << "NO" << endl;
            return;
        }
    }
    if (*max_element(c, c + n) > 2){
        cout << "NO" << endl;
        return;
    }

    // create graph
    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < n; i++){
        for (i64 j: d[a[i].first]){
            if (j != i){
                adj[i].emplace_back(j);
            }
        }
        for (i64 j: d[a[i].second]){
            if (j != i){
                adj[i].emplace_back(j);
            }
        }
    }

    vector<i64> colors(n, -1);
    queue<pair<i64, i64>> q;
    for (i64 i = 0; i < n; i++){
        if (colors[i] != -1) continue;
        q.emplace(i, 0);
        while (!q.empty()){
            auto[j, c] = q.front();
            q.pop();
            if (colors[j] != -1) continue; // already visited
            colors[j] = c;
            for (i64 k: adj[j]){
                if (colors[k] == c){
                    cout << "NO" << endl;
                    return;
                } else if (colors[k] == -1){
                    q.emplace(k, 1 - c);
                }
            }
        }
    }
    cout << "YES" << endl;
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
