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
if every x appears only once, not possible

choose some x which appears twice

-> choose some set with x
-> choose other set with 1
-> choose both

only impossible for all x if all sets have a unique element
*/

void solve(){
    i64 n, m;
    cin >> n >> m;
    vector<i64> cnt(m);
    vector<vector<i64>> sets(n);

    for (i64 i = 0; i < n; i++){
        i64 l;
        cin >> l;
        sets[i].resize(l);
        for (i64 j = 0; j < l; j++){
            cin >> sets[i][j];
            --sets[i][j];
            ++cnt[sets[i][j]];
        }
    }
    // has all
    for (i64 i = 0; i < m; i++){
        if (cnt[i] == 0){
            cout << "NO" << endl;
            return;
        }
    }

    // not all true ==> OR of not condition
    i64 has_unique_cnt = 0;
    for (i64 i = 0; i < n; i++){
        bool has_unique = false;
        for (i64 x: sets[i]){
            has_unique |= (cnt[x] == 1);
        }
        has_unique_cnt += has_unique;
    }
    cout << ((has_unique_cnt <= n - 2) ? "YES" : "NO") << endl;
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
