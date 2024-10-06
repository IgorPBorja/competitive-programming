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
    i64 n, m;
    cin >> n >> m;
    vector<vector<i64>> a(n, vector<i64>(m));
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }

    auto unstable = [&a, n, m](i64 i, i64 j){
        constexpr i64 dx[4] = {-1, 1, 0, 0};
        constexpr i64 dy[4] = {0, 0, -1, 1};
        bool is_unstable = true;
        i64 max_neighbors = -2e18;
        for (i64 k = 0; k < 4; k++){
            i64 x = i + dx[k], y = j + dy[k];
            if (x < 0 || x >= n || y < 0 || y >= m){
                continue;
            }
            is_unstable = is_unstable && (a[i][j] > a[x][y]);
            max_neighbors = max(max_neighbors, a[x][y]);
        }
        return make_pair(is_unstable, max_neighbors);
    };

    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            auto[is_unstable, max_neighbors] = unstable(i, j);
            if (is_unstable){
                a[i][j] = max_neighbors;
            }
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
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
