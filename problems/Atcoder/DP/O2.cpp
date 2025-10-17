// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		cerr << "G[" << u << "]="; \
		for (i64 v: G[u]) { \
			cerr << v << " "; \
		} \
		cerr << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

const int MOD = 1e9 + 7;

signed main(){
    int n;
    cin >> n;
    int a[n][n];
    vector<int> dp(1ll << n, 0);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    dp[0] = 1;  // empty matching
    for (int msk = 1; msk < (1ll << n); msk++){
        const int k = __builtin_popcount(msk);
        // k-1 because a is 0-indexed
        for (int j = 0; j < n; j++){
            if ((msk & (1ll << j)) && a[k - 1][j]) dp[msk] = (dp[msk] + dp[msk ^ (1ll << j)]) % MOD;
        }
    }
    cout << dp[(1ll << n) - 1] << endl;
}
