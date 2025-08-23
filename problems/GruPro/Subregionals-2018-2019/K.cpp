// #define TESTCASES
#define debug cout

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'

#define eb emplace_back
#define ep emplace
 
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
    vector<double> x(n), y(n), r(n);
    vector<tuple<double, double, double>> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> x[i] >> y[i] >> r[i];
        a[i] = make_tuple(r[i], x[i], y[i]);
    }
    sort(all(a));
    for(i64 i = 0; i < n; i++){
        r[i] = get<0>(a[i]);
        x[i] = get<1>(a[i]);
        y[i] = get<2>(a[i]);
    }
    double max_dist = (double)50 * sqrt((double)2);
    i64 p_end = 0;
    i64 intersections = 0;
    for (i64 i = 0; i < n; i++){
        while (p_end + 1 < n && r[p_end + 1] < r[i] + max_dist){
            ++p_end;
        }
        // intersection check: large radius <= small radius + distance
        // r[j] >= r[i] here
        for (i64 j = i + 1; j <= p_end; j++){
            double d = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
            if (r[j] <= r[i] + d){
                ++intersections;
            }
            if (intersections > n){
                cout << "greater" << endl;
                return;
            }
        }
    }
    cout << 2 * intersections << endl;
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
