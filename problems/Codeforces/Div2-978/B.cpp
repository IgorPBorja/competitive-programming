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

i64 f(vector<i64>& a, i64 x){
    if (a.size() == 0) return 0;
    if (a.size() == 1) return a[0];

    i64 s = 0;
    for (i64 b: a) s += b;
    vector<i64> ex;
    for (i64 b: a){
        if (b - (s + x - 1) / x > 0){
            ex.emplace_back(b - (s + x - 1) / x);
        }
    }
    // printmsg("ex=", ex.begin(), ex.end());
    return (s + x - 1) / x + f(ex, x);
}

void solve(){
    i64 n, x;
    cin >> n >> x;
    x = min(n, x);
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    cout << f(a, x) << endl;
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
