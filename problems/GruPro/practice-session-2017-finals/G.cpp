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

const i64 MAXN = 1e5 + 10;
const i64 MOD = (i64)1e9 + 7;
i64 dp[2][2][MAXN];  // dp[i][j][u] -> output i in free circuit, j in constrained
i64 state[MAXN];
i64 adj[2][MAXN];

void dfs_fill(i64 u){
    if (u == 0) return;

    for (i64 j = 0; j < 2; j++){
        dfs_fill(adj[j][u]);
    }

    if (state[u] != -1) return;  // already filled

    if (state[adj[0][u]] == 0){
        // 0 nand x = 1
        state[u] = 1;
    } else if (state[adj[1][u]] == 0){
        state[u] = 1;
    } else if (state[adj[0][u]] == 1 && state[adj[1][u]] == 1){
        state[u] = 0;
    }
}

void transition(i64 node, i64 tf, i64 tc){
    dp[tf][tc][node] = 0;
    for (i64 fi = 0; fi < 2; fi++){
        for (i64 fj = 0; fj < 2; fj++){
            for (i64 ci = 0; ci < 2; ci++){
                for (i64 cj = 0; cj < 2; cj++){
                    if (fi * fj != tf && ((ci * cj != tc) || state[node] == tc)){
                        dp[tf][tc][node] = (dp[tf][tc][node] + dp[fi][ci][adj[0][node]] * dp[fj][cj][adj[1][node]]) % MOD;
                    }
                }
            }
        }
    }
}

void dfs_solve(i64 node){
    if (node == 0){
        // already solved
        return;
    }
    for (i64 j = 0; j < 2; j++){
        dfs_solve(adj[j][node]);
    }

    if (state[node] == 0){
        dp[0][1][node] = dp[1][1][node] = 0;
        // fi, fj on free | ci, cj on constrained
        for (auto[tf, tc]: {make_pair(1, 0), make_pair(0, 0)}){
            transition(node, tf, tc);
        }
    } else if (state[node] == 1){
        dp[0][0][node] = dp[1][0][node] = 0;
        // fi, fj on free | ci, cj on constrained
        for (auto[tf, tc]: {make_pair(0, 1), make_pair(1, 1)}){
            transition(node, tf, tc);
        }
    } else {
        // free
        for (i64 tf = 0; tf < 2; tf++){
            for (i64 tc = 0; tc < 2; tc++){
                transition(node, tf, tc);
            }
        }
    }
}

void solve(){
    i64 n, a, b, st;
    cin >> n;
    for (i64 i = 1; i <= n; i++){
        cin >> a >> b >> st;
        // --a; --b;  // to 0-index
        state[i] = st;
        adj[0][i] = a;
        adj[1][i] = b;
    }

    state[0] = -1;
    dp[0][0][0] = dp[1][1][0] = 1;
    dp[0][1][0] = dp[1][0][0] = 0;
    // dfs_fill(1);  // root is 1, universal leaf 0
    dfs_solve(1);
    cout << (dp[0][1][1] + dp[1][0][1]) % MOD << endl;
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
