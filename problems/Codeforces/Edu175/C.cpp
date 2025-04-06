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

const i64 INF = (i64)2e9;

void solve(){
    i64 n, k;
    cin >> n >> k;
    vector<pair<i64, char>> windows;
    string colors;
    vector<i64> penalties(n);
    cin >> colors;
    for (i64 i = 0; i < n; i++){
        cin >> penalties[i];
    }
    char c = colors[0];
    i64 m = -INF;
    for (i64 i = 0; i < n; i++){
        char c2 = colors[i];
        i64 m2 = penalties[i];
        if (c != c2){
            windows.emplace_back(m, c);
            c = c2;
            m = -INF;
        }
        m = max(m2, m);
    }
    windows.emplace_back(m, c);
    if (windows.back().second == 'R'){
        windows.pop_back();
    }
    // printmsg("windows=", windows.begin(), windows.end());

    i64 lo = 0, hi = INF, ans = INF;
    while (lo <= hi){
        const i64 mid = lo + (hi - lo) / 2;
        i64 breaks = 0;
        vector<i64> merged;  // blue blocks after merge
        i64 cur = -INF;
        for (auto[m, c]: windows){
            if (c == 'R' && m > mid){
                ++breaks;
                merged.emplace_back(cur);
                cur = -INF;
            } else {
                cur = max(m, cur);
            }
        }
        if (cur > -INF) {
            merged.emplace_back(cur);
            ++breaks;
        }
        // cout << "at mid=" << mid << endl;
        // printmsg("merged=", merged.begin(), merged.end());
        // delete first breaks - k blocks
        i64 good_blue = 0;
        for (int x: merged){
            if (x <= mid) ++good_blue;
        }
        if (good_blue >= breaks - k){ // OK
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
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

