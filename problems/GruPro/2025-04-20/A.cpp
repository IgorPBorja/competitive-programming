#define TESTCASES
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

i64 vp(i64 x, i64 p){
    i64 y = 0;
    while (x > 0 && x % p == 0){
        ++y;
        x /= p;
    }
    return y;
}

void solve(){
    i64 n;
    cin >> n;
    i64 v2 = vp(n, 2), v3 = vp(n, 3);
    if (v2 > v3){
        cout << -1 << endl;
    } else {
        i64 tmp = n;
        for (i64 i = 0; i < v2; i++) tmp /= 2;
        for (i64 i = 0; i < v3; i++) tmp /= 3;
        if (tmp == 1){
            cout << v3 + (v3 - v2) << endl;
        } else {
            cout << -1 << endl;
        }
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
