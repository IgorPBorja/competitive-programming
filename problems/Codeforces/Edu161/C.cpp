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

const i64 INF = 2e18;

void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    i64 dir[n], next_cost[n], prev_cost[n];
    dir[0] = +1;
    next_cost[0] = 1;
    dir[n - 1] = -1;
    prev_cost[n - 1] = 1;
    for (i64 i = 1; i + 1 < n; i++){
        dir[i] = (a[i + 1] - a[i] < a[i] - a[i - 1]) ? 1 : -1;
        if (dir[i] == +1){
            next_cost[i] = 1;
            prev_cost[i] = a[i] - a[i - 1];
        } else {
            next_cost[i] = a[i + 1] - a[i];
            prev_cost[i] = 1;
        }
    }

    i64 pnext[n + 1], sprev[n + 1];
    pnext[0] = 0;
    for (i64 i = 0; i < n; i++){
        pnext[i + 1] = next_cost[i] + pnext[i];
    }
    // do the same sprev
    sprev[n] = 0;
    for (i64 i = n - 1; i >= 1; i--){
        sprev[i] = prev_cost[i] + sprev[i + 1];
    }
    sprev[0] = pnext[n] = INF;
    // printmsg("pnext=", pnext, pnext + n + 1);
    // printmsg("sprev=", sprev, sprev + n + 1);

    i64 m;
    cin >> m;
    for (i64 i = 0; i < m; i++){
        i64 x, y;
        cin >> x >> y;
        --x; --y;
        if (y > x){
            // x -> x + 1 -> ... -> y - 1 -> y
            // ANS = pnext[y] - pnext[x]
            cout << pnext[y] - pnext[x] << endl;
        } else if (y < x){
            // x -> x - 1 -> ... -> y + 1 -> y
            cout << sprev[y + 1] - sprev[x + 1] << endl;
        }
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
