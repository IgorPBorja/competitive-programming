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
    i64 n, m, q;
    cin >> n >> m >> q;

    vector<pair<i64, i64>> global;
    vector<i64> a_cnt(n + m), b_cnt(n + m);
    vector<i64> a(n), b(m);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        global.emplace_back(a[i], 0);
    }
    for (i64 i = 0; i < m; i++){
        cin >> b[i];
        global.emplace_back(b[i], 1);
    }
    sort(all(global));
    reverse(all(global));
    for (i64 i = 0; i < n + m; i++){
        a_cnt[i] = global[i].second == 0;
        b_cnt[i] = global[i].second == 1;
    }
    for (i64 i = 1; i < n + m; i++){
        a_cnt[i] += a_cnt[i - 1];
        b_cnt[i] += b_cnt[i - 1];
    }

    sort(all(a));
    reverse(all(a));
    sort(all(b));
    reverse(all(b));
    // prefix a, b
    for (i64 i = 1; i < n; i++) a[i] += a[i - 1];
    for (i64 i = 1; i < m; i++) b[i] += b[i - 1];

    for (i64 i = 0; i < q; i++){
        i64 x, y, z;
        cin >> x >> y >> z;
        if (z == 0){
            cout << 0 << endl;
            continue;
        }
        if (a_cnt[z - 1] > x){
            // a blocks
            i64 get_a = x, get_b = z - x;
            i64 total = 0;
            if (get_a > 0) total += a[get_a - 1];
            if (get_b > 0) total += b[get_b - 1];
            cout << total << endl;
        } else if (b_cnt[z - 1] > y){
            // b blocks
            i64 get_a = z - y, get_b = y;
            i64 total = 0;
            if (get_a > 0) total += a[get_a - 1];
            if (get_b > 0) total += b[get_b - 1];
            cout << total << endl;
        } else {
            i64 get_a = a_cnt[z - 1], get_b = b_cnt[z - 1];
            i64 total = 0;
            if (get_a > 0) total += a[get_a - 1];
            if (get_b > 0) total += b[get_b - 1];
            cout << total << endl;
        }
    }
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
