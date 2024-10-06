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
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

const i64 MOD = (i64)1e9 + 7;

i64 bexp(i64 a, i64 p){
    if (p == 0){
        return 1;
    } else {
        i64 m = bexp(a, p / 2);
        if (p % 2 == 1){
            return (((m * m) % MOD) * a) % MOD;
        } else {
            return (m * m) % MOD;
        }
    }
}

i64 inv(i64 a){
    return bexp(a, MOD - 2);
}

void solve(){
    i64 n, m, k;
    cin >> n >> m >> k;

    i64 f[m], fact[max(n, k) + 1];
    for (i64 i = 0; i < m; i++){
        i64 a, b;
        cin >> a >> b;  // ignored
        cin >> f[i];
    }

    if (m == 0){
        cout << 0 << endl;
        return;
    } else if (m == 1 && n == 2){
        cout << ((k * (k - 1) / 2) + k * f[0]) % MOD << endl;
        return;
    }

    // s[i]: how many ways I can assign (0, ..., m - 1) to a array of size i

    fact[0] = 1;
    for (i64 i = 1; i <= max(n, k); i++){
        fact[i] = (i * fact[i - 1]) % MOD;
    }

    auto choose = [&fact](i64 i, i64 j){
        i64 a = inv(fact[j]), b = inv(fact[i - j]);
        return (((fact[i] * a) % MOD) * b) % MOD;
    };


    i64 A = 0, B = 0;
    for (i64 c = 0; c <= k; c++){
        i64 modes = bexp((choose(n, 2) + MOD - 1) % MOD, k - c);  // options: any edge except the selected one
        A = (A + (((choose(k, c) * modes) % MOD) * c) % MOD) % MOD;
        i64 c2 = ((c * (c - 1)) >> 1) % MOD;
        B = (B + (((choose(k, c) * modes) % MOD) * c2) % MOD) % MOD;
    }

    i64 ans = (m * B) % MOD;
    for (i64 i = 0; i < m; i++){
        ans = (ans + f[i] * A) % MOD;
    }
    ans = (ans * inv(bexp(choose(n, 2), k))) % MOD;
    cout << ans << endl;
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
