// #define TESTCASES

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
    i64 n, r, c;
    cin >> n >> r >> c;
    vector<i64> active(n, true);
    i64 removed = 0;
    vector<i64> hired;

    i64 i = 0, seen_i = 1, j = n - 1, seen_j = 1;
    while (removed < n - 2){  // more than 2
        i64 k = n - removed;
        // take as many k as possible (complete cycles) such that 
        // r - k * q > 0 ==> k * q <= r - 1
        i64 c2 = c - k * ((c - 1) / k), r2 = r - k * ((r - 1) / k);

        while (seen_i < r2){
            seen_i += active[(i + 1) % n];
            i = (i + 1) % n;
        }
        // when stopped now i is in correct pos
        while (seen_j < c2){
            seen_j += active[(j + n - 1) % n];
            j = (j + n - 1) % n;
        }
        cerr << "stopped at i=" << i << " j=" << j << endl;
        if (i == j){
            // hire him
            hired.emplace_back(i);
            ++removed;
            active[i] = false;
        } else {
            active[i] = false;
            active[j] = false;
            removed += 2;
        }
        seen_i = 0;
        seen_j = 0;
    }
    for (i64 i = 0; i < n; i++) if (active[i]) hired.emplace_back(i);

    sort(all(hired));
    for (i64 x: hired){
        cout << x + 1 << " ";
    }
    cout << endl;
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
