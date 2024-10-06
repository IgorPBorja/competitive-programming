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
std::ostream& operator<< (std::ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 MOD = (i64)1e9 + 7;

template<typename A, typename B, typename C>
tuple<A, B, C> operator+(tuple<A, B, C> t1, tuple<A, B, C> t2){
    tuple<A, B, C> t;
    get<0>(t) = (get<0>(t1) + get<0>(t2)) % MOD;
    get<1>(t) = (get<1>(t1) + get<1>(t2)) % MOD;
    get<2>(t) = (get<2>(t1) + get<2>(t2)) % MOD;
    return t;
}
template<typename A, typename B, typename C>
tuple<A, B, C> operator-(tuple<A, B, C> t1, tuple<A, B, C> t2){
    tuple<A, B, C> t;
    get<0>(t) = (get<0>(t1) + MOD - get<0>(t2)) % MOD;
    get<1>(t) = (get<1>(t1) + MOD - get<1>(t2)) % MOD;
    get<2>(t) = (get<2>(t1) + MOD - get<2>(t2)) % MOD;
    return t;
}

template<typename A, typename B, typename C>
std::ostream& operator<<(std::ostream& out, tuple<A, B, C> t){
    out << get<0>(t) << "," << get<1>(t) << "," << get<2>(t);
    return out;
}

void solve(){
    i64 n, m, b, c, d;
    cin >> n >> m >> b >> c >> d;
    vector<i64> L(n), R(n), a(n);
    for (i64 i = 0; i < n; i++){
        cin >> L[i];
        --L[i];
    }
    for (i64 i = 0; i < n; i++){
        cin >> R[i];
        --R[i];
    }
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    for (i64 j = 0; j < m; j++){
        // coefficient vector
        vector<tuple<i64, i64, i64>> coef(n, tuple<i64, i64, i64>(0, 0, 0));
        // simulate prefix on L[i], R[i]
        for (i64 i = 0; i < n; i++){
            tuple<i64, i64, i64> diff = {(a[i] * b) % MOD, (a[i] * c) % MOD, (a[i] * d) % MOD};
            coef[L[i]] = coef[L[i]] + diff;
            if (R[i] + 1 < n){
                coef[R[i] + 1] = (coef[R[i] + 1] - diff);
            }
        }
        // prefix it
        for (i64 i = 1; i < n; i++){
            coef[i] = coef[i] + coef[i - 1];
        }
        
        // apply
        for (i64 i = 0; i < n; i++){
            auto[c2, c1, c0] = coef[i];
            // +1 because of one-indexing
            i64 x2 = (c2 * (((i + 1) * (i + 1)) % MOD)) % MOD;
            i64 x1 = (c1 * (i + 1)) % MOD, x0 = c0;
            a[i] = (a[i] + x2 + x1 + x0) % MOD;
        }
    }
    for (i64 i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
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
