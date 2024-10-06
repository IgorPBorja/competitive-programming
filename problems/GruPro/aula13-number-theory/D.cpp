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

vector<i64> primes;  // O(sqrt(n) / log(sqrt(n))) = O(sqrt(n) / logn) ~ 10^3

void sieve(){
    const i64 M = 1e5;
    vector<bool> composite(M + 1, false);
    for (i64 i = 2; i <= M; i++){
        if (composite[i]) continue;
        primes.emplace_back(i);
        for (i64 j = 2 * i; j <= M; j += i){
            composite[j] = true;
        }
    }
}

void solve(){
    i64 n, x;
    cin >> n;
    unordered_map<i64, i64> cnt;
    // printmsg("p=", primes.begin(), primes.end());
    bool ok = false;
    for (i64 i = 0; i < n; i++){
        cin >> x;
        for (i64 p: primes){
            if (p * p > x) break;
            if (x % p != 0) continue;
            ++cnt[p];
            while (x % p == 0) x /= p;
        }
        if (x > 1) ++cnt[x];
    }
    for (const auto[p, c]: cnt){
        if (c > 1) ok = true;
    }
    cout << (ok ? "YES" : "NO") << endl;
}
 
signed main(){
	fastio;
    sieve();

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
