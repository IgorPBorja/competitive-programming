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

/*
for zero sequence: take sorted!
*/

void build(vector<i64>& p, i64 pl, i64 pr, i64 vl, i64 vr){
    // build derangement
    for (i64 i = pl; i <= pr; i++){
        i64 offset = i - pl;
        i64 mod = (offset + 1) % (vr - vl + 1);
        p[i] = vl + mod;
    }
}

void solve(){
    i64 n;
    cin >> n;
    string _s;
    cin >> _s;
    vector<i64> s(n);
    for (i64 i = 0; i < n; i++) s[i] = _s[i] - '0';

    vector<i64> p(n);
    i64 last = -1;
    for (i64 i = 0; i < n; i++){
        if (s[i] == 0){
            // skip
        } else {
            // we have fixed point
            p[i] = i;
            if (last + 1 == i - 1){
                // not possible to have no fixed points
                cout << "NO" << endl;
                return;
            }
            build(p, last + 1, i - 1, last + 1, i - 1);
            last = i;
        }
    }
    if (last != n - 1) { // s[n - 1] = 0
        if (last + 1 == n - 1){
            // not possible to have no fixed points
            cout << "NO" << endl;
            return;
        }
        build(p, last + 1, n - 1, last + 1, n - 1);
    }

    cout << "YES" << endl;
    for (i64 i = 0; i < n; i++){
        cout << p[i] + 1 << " ";
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
