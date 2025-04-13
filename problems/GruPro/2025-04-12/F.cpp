// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 INF = (i64)2e18;

i64 merge(i64 op_code, i64 x, i64 y){
    if (op_code == 0){
        return x | y;
    } else {
        return x ^ y;
    }
}

struct AlternatingMerge{
    i64 n, sz;
    vector<i64> v;

    // 2^n --> 2^{n + 1} - 1
    AlternatingMerge(const vector<i64> a, i64 n) : n(n), sz((1ll << (n + 1)) - 1) {
        // level 0
        v.resize(sz);
        for (i64 i = 0; i < (1ll << n); i++){
            v[i] = a[i];
        }
        // level i --> 2^{n - i} terms
        for (i64 i = 1; i <= n; i++){
            for (i64 j = 0; j < (1ll << (n - i)); j++){
                // 2 * j elements after start of previous level
                i64 prev_start = level_start(i - 1);
                i64 merge_pos = prev_start + 2 * j;
                i64 start = level_start(i);
                i64 pos = start + j;
                i64 op = (i - 1) % 2;
                v[pos] = merge(op, v[merge_pos], v[merge_pos + 1]);
            }
        }
    }

    i64 level_start(i64 level){
        // at level i
        // 2^n + ... + 2^{n-(i-1)} = 2^{n-i+1} * (1 + ... + 2^{i-1})
        // = 2^{n-i+1}(2^{i} - 1) = 2^{n+1} - 2^{n-i+1}
        return (1ll << (n + 1)) - (1ll << (n + 1 - level));
    }

    i64 query_all(){
        return v.back();
    }

    void update(i64 p, i64 b, i64 op = 0, i64 level = 0){
        v[p] = b;
        if (level == n) return;

        // p+1 is p is even, p-1 if p is odd
        i64 pair_pos = p + ((p % 2 == 0) ? 1 : -1);
        i64 prop = merge(op, v[p], v[pair_pos]);
        
        i64 start = level_start(level);
        i64 delta = p - start;
        // merge pos is (start of next level + delta / 2)
        i64 merge_pos = level_start(level + 1) + delta / 2;
        update(merge_pos, prop, 1 - op, level+1);
    }
};

void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<i64> a((1ll << n));
    for (i64 i = 0; i < (1ll << n); i++){
        cin >> a[i];
    }
    AlternatingMerge S(a, n);
    // printmsg("v=", S.v.begin(), S.v.end());
    for (i64 i = 0; i < q; i++){
        i64 p, b;
        cin >> p >> b;
        --p;  // 0-indexed
        S.update(p, b);
        // printmsg("v=", S.v.begin(), S.v.end());
        cout << S.query_all() << endl;
    }
}
 
signed main(){
	fastio;
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
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
