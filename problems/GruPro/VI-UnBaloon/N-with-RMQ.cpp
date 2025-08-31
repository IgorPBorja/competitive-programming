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

struct MinMaxRMQ {
    i64 n;
    i64 LOG;
    vector<vector<i64>> min_table, max_table;
    
    MinMaxRMQ(const vector<i64>& a) : n(a.size()) {
        LOG = 0;
        for (; (1ll << LOG) <= n; LOG++) {}

        min_table.resize(LOG + 1);
        max_table.resize(LOG + 1);
        for (i64 i = 0; i <= LOG; i++) min_table[i].resize(n);
        for (i64 i = 0; i <= LOG; i++) max_table[i].resize(n);
        copy(all(a), min_table[0].begin());
        copy(all(a), max_table[0].begin());
        for (i64 lvl = 1; lvl <= LOG; lvl++){
            i64 delta = 1ll << (lvl - 1);
            for (i64 i = 0; i < n; i++){
                min_table[lvl][i] = (i + delta < n) ? 
                    min(min_table[lvl - 1][i], min_table[lvl - 1][i + delta])
                    : min_table[lvl - 1][i];
                max_table[lvl][i] = (i + delta < n) ? 
                    max(max_table[lvl - 1][i], max_table[lvl - 1][i + delta])
                    : max_table[lvl - 1][i];
            }
        }
    }

    // inclusive [l, r] query for min and max
    pair<i64, i64> query(i64 l, i64 r){
        i64 p2 = 1, lvl = 0;
        // range goes from l to l+p2-1 (inclusive)
        for (; l + (2 * p2) <= r + 1; p2 <<= 1, lvl++) {}
        // guaranteed now [l, l + p2) U [r + 1 - p2, r + 1)
        // covers full interval 
        // since 2 * p2 >= delta (otherwise loop would not have stopped)
        return {
            min(min_table[lvl][l], min_table[lvl][r - p2 + 1]),
            max(max_table[lvl][l], max_table[lvl][r - p2 + 1])
        };
    }

    // since all values in array are distinct, is permutation
    // iff min value is 1 and max value is range size
    bool is_permutation(i64 l, i64 r){
        auto[m, M] = query(l, r);
        return m == 1 && M == r - l + 1;
    }
};

void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    
    MinMaxRMQ rmq(a);
    for (i64 i = 0; i < q; i++){
        i64 l, r;
        cin >> l >> r;
        --l; --r;
        cout << (rmq.is_permutation(l, r) ? "TAK" : "NIE") << endl;
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
