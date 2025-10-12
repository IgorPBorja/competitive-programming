// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) debug << msg; for(auto it = v.begin(); it != v.end(); it++){debug << *it << " ";} debug << endl;
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

// 2^22 > 4*10^6
const i64 B = 22;

void solve(){
    i64 n;
    cin >> n;
    vector<i64> a(n), ok(1ll << B, -1);
    for (i64 i = 0; i < n; i++) {
        cin >> a[i];
        ok[a[i]] = a[i];
    }

    // sosdp[i][mask] = any element which is a submask of mask
    // and matches at 2^{B-1}...2^i
    // else -1
    vector<i64> sosdp(1ll << B);
    sosdp = ok;
    for (i64 i = 0; i < B; i++){
        // matching 2^{B-1}..2^i
        // either matches 2^i, or matches 2^i at mask ^ 2^i
        // do in reverse order so we can use a single array
        // since mask will only look at smaller values
        for (i64 mask = (1ll << B) - 1; mask >= 0; mask--){
            if ((mask & (1ll << i)) && sosdp[mask] == -1 && sosdp[mask ^ (1ll << i)] != -1)
                sosdp[mask] = sosdp[mask ^ (1ll << i)];
        }
    }
    for (i64 i = 0; i < n; i++){
        cout << sosdp[((1ll << B) - 1) ^ a[i]] << " ";
    }
    cout << endl;
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
