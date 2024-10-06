// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
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


// pre-read all distinct values there will be and put in sorted vector D of size k
// then define idx(a) := index of a in D
// Build seg on top of count vector cnt[k]
// where cnt[i] = #(salaries equal to D[i])
// then #(amount of salaries between a and b) = sum(i=idx(a')...idx(b') - 1)cnt[i]
// where a' = lower_bound(a, D) and b' = upper_bound(b, D)

struct SumSeg {
    vector<i64> seg;
    i64 n;

    SumSeg(const vector<i64> &a) : n(n) {
        seg.resize(4 * n);
    }
};

void solve(){
    i64 n, q;
    cin >> n >> q;

    vector<i64> a(n);
    set<i64> _D;
    vector<tuple<i64, i64, i64>> queries(q);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        _D.insert(a[i]);
    }
    for (i64 i = 0; i < q; i++){
        string type;
        i64 a, b, k, x;
        cin >> type;
        if (type == "?"){
            cin >> a >> b;
            queries[i] = {0, a, b};
        } else {
            cin >> k >> x;
            --k;
            queries[i] = {1, k, x};
            _D.insert(x);
        }
    }
    vector<i64> D;
    for (auto x: _D){
        D.emplace_back(x);
    }

    vector<i64> cnt(D.size(), 0);
    for (i64 i = 0; i < n; i++){
        ++cnt[lower_bound(D.begin(), D.end(), a[i]) - D.begin()];
    }

    SumSeg seg(cnt);
    
    for (i64 i = 0; i < q; i++){
        if (get<0>(queries[i]) == 0){
            // ask
            i64 a = get<1>(queries[i]), b = get<2>(queries[i]);
            i64 idx_a = lower_bound(D.begin(), D.end(), a) - D.begin(),
                idx_b = upper_bound(D.begin(), D.end(), b) - D.begin() - 1;
            cout << seg.query(idx_a, idx_b) << endl;
        } else {
            i64 k = get<1>(queries[i]), x = get<2>(queries[i]);
            seg.update(k, x);
        }
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
