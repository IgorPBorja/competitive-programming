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
    i64 n;
    cin >> n;

    vector<i64> dp(n);
    map<i64, vector<i64>> per_size;
    for (i64 i = 0; i < n; i++){
        cout << "? " << i + 1 << " " << n << " ";
        for (i64 j = 0; j < n; j++){
            cout << j + 1 << " ";
        }
        cout << endl;
        cout.flush();
        cin >> dp[i];
        per_size[dp[i]].emplace_back(i);
    }

    // choose any starting point
    i64 s = -1, d = 0;
    for (i64 i = 0; i < n; i++){
        if (dp[i] > d){
            d = dp[i];
            s = i;
        }
    }
    vector<i64> path = {s};
    for (i64 sz = d - 1; sz >= 1; sz--){
        i64 t = -1;
        for (auto v: per_size[sz]){
            cout << "? " << s + 1 << " " << 2 << " " << s + 1 << " " << v + 1 << endl;
            cout.flush();
            i64 len;
            cin >> len;
            if (len == 2){
                t = v;
                break;
            }
        }
        path.emplace_back(t);
        s = t;
    }
    cout << "! " << d << " ";
    for (i64 v: path){
        cout << v + 1 << " ";
    }
    cout << endl;
    cout.flush();
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
