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

const i64 MOD = 998244353;

i64 bexp(i64 a, i64 p){
    if (p == 0) {
        return 1;
    } else {
        i64 b = bexp(a, p / 2);
        if (p % 2 == 0){
            return (b * b) % MOD;
        } else {
            return (a * ((b * b) % MOD)) % MOD;
        }
    }
}

i64 inv(i64 x) {
    return bexp(x, MOD - 2);
}

void solve(){
    i64 n;
    cin >> n;
    i64 w = 1;
    for (i64 i = 0; i < n / 3; i++){
        i64 t[3];
        cin >> t[0] >> t[1] >> t[2];
        i64 ways = 0, m = min(t[0], min(t[1], t[2]));
        for (i64 j = 0; j < 3; j++){
            ways += (t[j] == m);
        }
        w = (w * ways) % MOD;
    }

    i64 fact[n / 3 + 1];
    fact[0] = 1;
    for (i64 i = 1; i <= n / 3; i++){
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    i64 c = (((fact[n / 3] * inv(fact[n / 6])) % MOD) * inv(fact[n / 6])) % MOD;
    cout << (c * w) % MOD << endl;
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
