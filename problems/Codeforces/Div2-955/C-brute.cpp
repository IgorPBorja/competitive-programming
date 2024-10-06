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
    i64 n, l, r;
    cin >> n >> l >> r;

    i64 a[n], dp[n + 1], pref[n + 1];
    pref[0] = 0;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }

    auto bounds = [&pref, l, r](i64 i){
        // find first idx s.t suffix (j,...,i) is <= r
        i64 j;
        for (j = 0; j <= i; j++){
            if (pref[i + 1] - pref[j] <= r) break;
        }
        if (j > i) return pair<i64, i64>(-1, -1);

        // find last idx s.t suffix (k,...,i) is >= l
        if (pref[i + 1] < l) return pair<i64, i64>(-1, -1);
        i64 k = 0;
        // can include k + 1
        while (k + 1 <= i && pref[i + 1] - pref[k + 1] >= l){
            ++k;
        }
        if (j > k) return pair<i64, i64>(-1, -1);
        return pair<i64, i64>(j, k);
    };

    auto range_max = [&dp](i64 a, i64 b){
        i64 s = dp[a];
        for (i64 i = a + 1; i <= b; i++){
            s = max(s, dp[i]);
        }
        return s;
    };

    dp[0] = 0;
    for (i64 i = 0; i < n; i++){
        auto[j, k] = bounds(i);
        // cout << "i=" << i << " j=" << j << " k=" << k << endl;
        if (j == -1 && k == -1){
            dp[i + 1] = dp[i];
        } else {
            // j...k are the starting points on the array
            // ==> can grab up to j-1...k-1 ==> max dp[j..k]
            dp[i + 1] = range_max(j, k) + 1;
        }
    }
    // printmsg("dp=", dp, dp + n + 1);
    cout << dp[n] << endl;
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
