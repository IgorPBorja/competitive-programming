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

void solve(){
    i64 n, k;
    cin >> n >> k;
    vector<i64> s(n), t(n);
    for (i64 i = 0; i < n; i++){
        cin >> s[i];
    }
    for (i64 i = 0; i < n; i++){
        cin >> t[i];
    }
    set<i64> seen_pos;  // positive remainders: 0 1 2 -1 -2
    // r <= x-r ==> 2r <= x
    
    map<i64, i64> t_cnt, s_cnt;
    for (i64 i = 0; i < n; i++){
        t_cnt[t[i] % k]++;
        s_cnt[s[i] % k]++;
        // if (2 * (s[i] % k) <= k){
            seen_pos.emplace(s[i] % k);
        // }
    }
    bool ok = true;
    for (i64 x: seen_pos){
        ok &= (t_cnt[x] + t_cnt[(k - x) % k]) == (s_cnt[x] + s_cnt[(k - x) % k]);
    }
    
    cout << (ok ? "YES" : "NO") << endl;
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

