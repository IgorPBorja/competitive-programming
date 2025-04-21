// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
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

i64 isqrt(i64 x){
    // x is at most 10^12
    i64 l = 1, r = min((i64)(1e6) + 10, x);
    while (l <= r){
        const i64 m = l + (r - l) / 2;
        const i64 y = m * m;
        if (y == x) {
            return m;
        } else if (y > x){
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return -1;
}

// yz = a1
// zx = a2
// xy = a3
// p = xyz = sqrt(a1 * a2 * a3)
// x = p/a1, y = p/a2, z = p/a3
// s = 4 * (x + y + z)
void solve(){
    i64 a1, a2, a3;
    cin >> a1 >> a2 >> a3;
    i64 p = isqrt(a1 * a2 * a3);
    i64 x = p/a1, y = p/a2, z = p/a3;
    cout << 4ll * (x + y + z) << endl;
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
