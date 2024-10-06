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

template<typename T>
T minv(T x, T y){
    return min(x, y);
}
template<typename... T, typename U>
U minv(U x, T... vars){
    return min(x, minv(vars...));
}
template<typename T>
T maxv(T x, T y){
    return max(x, y);
}
template<typename... T, typename U>
U maxv(U x, T... vars){
    return max(x, maxv(vars...));
}

void solve(){
    i64 n;
    cin >> n;

    i64 dpmax[n + 1], dpmin[n + 1];
    dpmax[0] = dpmin[0] = 0;
    for (i64 i = 1; i <= n; i++){
        i64 a;
        cin >> a;
        dpmin[i] = dpmin[i - 1] + a;
        dpmax[i] = maxv(abs(dpmin[i - 1] + a), abs(dpmax[i - 1] + a));
    }

    cout << dpmax[n] << endl;
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
