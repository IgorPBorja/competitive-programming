#define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
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

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 INF = 2e18;

void solve(){
    string s;
    cin >> s;
    const i64 n = s.size();
    i64 cnt[3] = {0, 0, 0};
    i64 best = INF;
    #define bad (!cnt[0] || !cnt[1] || !cnt[2])
    // #define show cout << "cnt=[" << cnt[0] << " " << cnt[1] << " " << cnt[2] << "]" << endl
    i64 r = 0;  // half-open close
    for (i64 l = 0; l < n; l++){
        if (l > 0 && r > l - 1) {
            --cnt[s[l - 1] - '1'];  // had l - 1
        }
        r = max(r, l);
        while (r < n && bad) {
            ++cnt[s[r++] - '1'];
        }
        // show;
        // cout << "l=" << l << " r=" << r << endl;
        if (!bad){
            best = min(best, r - l);
        }
    }
    cout << (best == INF ? 0 : best) << endl;
}
 
signed main(){
	fastio;
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
