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

template<typename T>
T minv(T x, T y){
    return min(x, y);
}
template<typename... T, typename U>
U minv(U x, T... vars){
    return min(x, minv(vars...));
}
template<typename T>
T maxv(T x, T y){
    return max(x, y);
}
template<typename... T, typename U>
U maxv(U x, T... vars){
    return max(x, maxv(vars...));
}

const i64 MOD = 998244353;

void solve(){
    i64 n;
    cin >> n;

    i64 dpmax[n + 1], dpmin[n + 1];
    dpmax[0] = dpmin[0] = 0;
    i64 cntmax[n + 1], cntmin[n + 1];
    cntmax[0] = 1; cntmin[0] = 1;
    for (i64 i = 1; i <= n; i++){
        i64 a;
        cin >> a;
        dpmin[i] = dpmin[i - 1] + a;
        cntmin[i] = (dpmin[i - 1] + a >= 0) ? (2 * cntmin[i - 1]) % MOD : cntmin[i - 1];
        dpmax[i] = max(abs(dpmin[i - 1] + a), abs(dpmax[i - 1] + a));

        pair<i64, i64> values[4] = {
            {dpmin[i - 1] + a, cntmin[i - 1]},
            {abs(dpmin[i - 1] + a), cntmin[i - 1]},
            {dpmax[i - 1] + a, cntmax[i - 1]},
            {abs(dpmax[i - 1] + a), cntmax[i - 1]},
        };

        cntmax[i] = 0;
        for (i64 j = 0; j < 4; j++){
            if (values[j].first == dpmax[i]){
                cntmax[i] += values[j].second;
            }
        }
        if (dpmin[i - 1] == dpmax[i - 1]){
            cntmax[i] >>= 1;
        }
        cntmax[i] %= MOD;
    }

    // printmsg("dpmin=", dpmin, dpmin + n + 1);
    // printmsg("dpmax=", dpmax, dpmax + n + 1);
    //
    // printmsg("cntmin=", cntmin, cntmin + n + 1);
    // printmsg("cntmax=", cntmax, cntmax + n + 1);
    cout << cntmax[n] << endl;
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
