#define testcases

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(null);cout.tie(null)
#define endl '\n'
 
#define i64 int64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, g) cerr << msg << endl; \
	for (i64 u = 0; u < g.size(); u++) { \
		cerr << "g[" << u << "]="; \
		for (i64 v: g[u]) { \
			cerr << v << " "; \
		} \
		cerr << endl; \
	}
 
template <typename t, typename u>
ostream& operator<< (ostream& out, pair<t, u> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename t>
ostream& operator<< (ostream& out, vector<t> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename t>
using min_pq = priority_queue<t, vector<t>, greater<t>>;
template <typename t>
using max_pq = priority_queue<t>;

void solve(){
    /*
    the benefit from decreasing a[i] is:
    * -1 if it is not connected to the right
    * p where p is the number of consecutive columns to the left with that row filled
    
    a[j] connects to a[i] if a[j] >= a[i]

    a[i] is connected to the right iff min(a[i+1..n-1]) >= a[i]

    row r <= a[i] on column i moves iff min(a[i+1..n-1]) < a[i]

    therefore for each column the original number of blocks moved is max(a[i] - suf_min[i + 1], 0)
    */

    i64 n;
    cin >> n;
    vector<i64> a(n), suf_min(n);
    for (i64 i = 0; i < n; i++) cin >> a[i];
    suf_min[n - 1] = a[n - 1];
    for (i64 i = n - 2; i >= 0; i--) suf_min[i] = min(a[i], suf_min[i + 1]);

    vector<i64> is_right_connected(n, false);
    is_right_connected[n - 1] = true;
    for (i64 i = 0; i < n - 1; i++) is_right_connected[i] = (suf_min[i + 1] >= a[i]);

    i64 original_moved = 0;
    for (i64 i = 0; i < n - 1; i++) original_moved += max(a[i] - suf_min[i + 1], (i64)0);

    vector<i64> last_pos_smaller(n + 1, -1);
    i64 r = n;
    for (i64 i = n - 1; i >= 0; i--){
        while (a[i] < r){
            last_pos_smaller[r] = i;
            --r;
        }
    }

    i64 delta = 0;
    for (i64 i = 0; i < n; i++){
        // try decreasing a[i]
        if (!is_right_connected[i]) continue; // won't bring any benefits, this will already move anyway
        else {
            // p where p is the number of consecutive columns to the left with that row filled
            // i.e a[j..i-1] where min(a[j..i-1]) >= a[i]
            // i.e a[j-1] is the last where a[j-1] < a[i]
            // we can use a seg tree for that
            i64 p = (i - 1) - last_pos_smaller[a[i]];  // j..i-1 where last_pos_smaller[a[i]] = j-1
            delta = max(delta, p);
        }
    }
    cout << original_moved + delta << endl;
}
 
signed main(){
	fastio;
	int t = 1;
#ifdef testcases
	cin >> t;
#endif
	while (t--){
		solve();
	}
}
