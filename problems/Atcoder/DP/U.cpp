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

i64 dp[1ll << 20];
i64 sum[1ll << 20];
const i64 INF = 1e18;

void solve(){
    i64 n;
    cin >> n;
    i64 a[n][n];
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }

    for (i64 i = 0; i < (1ll << 20); i++){
        dp[i] = -INF;
        sum[i] = 0;
        for (i64 j = 0; j < n; j++){
            for (i64 k = j + 1; k < n; k++){
                if ((i & (1ll << j)) && (i & (1ll << k))){
                    sum[i] += a[j][k];
                }
            }
        }
    }

    dp[0] = 0;
    dp[1] = 0;
    for (i64 i = 1; i < n; i++){
        // choose h as a mask for the others
        for (i64 h = 0; h < (1ll << i); h++){
            // choose g as group for i
            const i64 b = __builtin_popcount(h);
            for (i64 compressed_g = 0; compressed_g < (1ll << b); compressed_g++){
                // build g
                i64 g = 0;
                for (i64 j = 0, cnt = 0; j < i; j++){
                    if (h & (1ll << j)){
                        g += ((compressed_g & (1ll << cnt)) >> cnt) << j;
                        ++cnt;
                    }
                }
                dp[h | (1ll << i)] = max(dp[h | (1ll << i)], sum[g | (1ll << i)] + dp[h & ~g]);
            }
        }
    }
    cout << *max_element(dp, dp + (1ll << n)) << endl;
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
