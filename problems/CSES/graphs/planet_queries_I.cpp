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

// O(n log M) binary lift table precalculation
vector<vector<i64>> blift(vector<i64> f, i64 M){
    // get integer logarithm
    const i64 n = f.size();
    i64 ilog = 0;
    while (1ll << (ilog + 1) <= M){
        ++ilog;
    }
    vector<vector<i64>> f_lifted(ilog + 1, vector<i64>(n));
    for (i64 i = 0; i < n; i++){
        f_lifted[0][i] = f[i];
    }
    for (i64 j = 1; j <= ilog; j++){
        for (i64 i = 0; i < n; i++){
            f_lifted[j][i] = f_lifted[j - 1][f_lifted[j - 1][i]];
        }
    }
    return f_lifted;
}

// O(log M) function composition
i64 apply_compose(vector<vector<i64>> &f_lifted, i64 x, i64 k){
    i64 d = f_lifted.size();
    for (i64 i = 0; i < d; i++){
        if (k & (1ll << i)){
            x = f_lifted[i][x];
        }
    }
    return x;
}

void solve(){
    i64 n, q; 
    cin >> n >> q;
    vector<i64> f(n);
    for (i64 i = 0; i < n; i++){
        cin >> f[i];
        --f[i];  // 0-index
    }


    vector<vector<i64>> f_lifted = blift(f, (i64)1e9 + 1);
    // printmsg("f=", f.begin(), f.end());
    // printgraph("f lifted:", f_lifted);
    for (i64 i = 0; i < q; i++){
        i64 x, k;
        cin >> x >> k;
        --x;  // 0-index
        cout << apply_compose(f_lifted, x, k) + 1 << endl;
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
