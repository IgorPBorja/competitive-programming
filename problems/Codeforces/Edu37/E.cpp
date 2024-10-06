//#define TESTCASES
    
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
    
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
    
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
    out << x.first << " " << x.second;
    return out;
}
    
void solve(){
    i64 n, m, x, y;
    cin >> n >> m;
    vector<vector<i64>> adj(n);
    
    for (i64 i = 0; i < m; i++){
        cin >> x >> y;
        --x;
        --y;
        adj[x].eb(y);
        adj[y].eb(x);
    }
    for (i64 i = 0; i < n; i++){
        adj[i].eb(i);
    }
    
    i64 max_comp = 0;
    // lets use a dsu-like small-to-large approach
    vector<i64> parent(n, -1);
    for (i64 i = 0; i < n; i++){
        sort(adj[i].begin(), adj[i].end());
        for (i64 j = 0; j < adj[i].size(); j++){
            if (adj[i][j] > j){
                // same connected component of adj[i][j] - 1
                if (parent[]){
                    // create component
                    parent[i] = -1;
                    ++max_comp;
                } else {
                    parent[i] = parent[adj[i][j] - 1];
                }
                break;
            }
        }
        if (parent[i] == -1 && adj[i].size() < n){
            // its a prefix w/ size < n
            if (adj[i].size() < i){
                parent[i] = parent[adj[i].size()];
            } else {
                parent[i] = max_comp;
                ++max_comp;
            }
        }
    }
    for (i64 i = 0; i < n; i++){
        // isolated
        if (parent[i] == -1){
            parent[i] = max_comp;
            ++max_comp;
        }
    }
    
    vector<i64> cmp_sizes(max_comp, 0);
    for (i64 i = 0; i < n; i++){
        ++cmp_sizes[parent[i]];
    }
    sort(cmp_sizes.begin(), cmp_sizes.end());
    
    cout << max_comp << endl;
    for (i64 s: cmp_sizes){
        cout << s << " ";
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