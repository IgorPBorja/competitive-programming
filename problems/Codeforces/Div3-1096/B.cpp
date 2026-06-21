#define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		cerr << "G[" << u << "]="; \
		for (i64 v: G[u]) { \
			cerr << v << " "; \
		} \
		cerr << endl; \
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
    // let s be any sequence where cnt[open] = cnt[closed]
    // we can translate into integer seq a[1..n] where ( = +1 and ) = -1
    // and we take the prefix
    // then removing a range l..r is the same as subtracting a[r]-a[l-1] from everything
    // so we can always take the minimum range (most closing parenthesis) and put at the end
    // that we will have min(a') = 0

    i64 n;
    cin >> n;
    string s;
    cin >> s;
    i64 open = 0, closed = 0;
    for (i64 i = 0; i < n; i++){
        if (s[i] == '(') ++open;
        else ++closed;
    }
    if (open == closed) { cout << "YES" << endl; }
    else cout << "NO" << endl;
}
 
signed main(){
	fastio;
	int t = 1;
#ifdef TESTCASES
	cin >> t;
#endif
	while (t--){
		solve();
	}
}
