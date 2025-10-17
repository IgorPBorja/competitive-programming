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

struct AlternatingORTree {
    vector<i64> seg;
    i64 s;

    AlternatingORTree(const vector<i64> &a) : s(a.size()) {
        seg.resize(4 * s);
        build(a, 0, s - 1, 0);
    }

    // returns operation code: 0 for OR, 1 for XOR
    i64 build(const vector<i64> &a, i64 l, i64 r, i64 node){
        if (l == r){
            seg[node] = a[l];
            return 1;
        }

        const i64 m = l + (r - l) / 2;
        const i64 prev_type = build(a, l, m, 2 * node + 1);
        build(a, m + 1, r, 2 * node + 2);

        const i64 type = 1 - prev_type;
        if (type == 0){
            seg[node] = seg[2 * node + 1] | seg[2 * node + 2];
        } else {
            seg[node] = seg[2 * node + 1] ^ seg[2 * node + 2];
        }
        return type;
    }

    // returns operation code: 0 for OR, 1 for XOR
    i64 pt_update(i64 p, i64 x, i64 l, i64 r, i64 node) {
        if (l == r && r == p){
            seg[node] = x;
            return 1;
        }

        const i64 m = l + (r - l) / 2;
        i64 prev_type;
        if (p <= m){
            prev_type = pt_update(p, x, l, m, 2 * node + 1);
        } else {
            prev_type = pt_update(p, x, m + 1, r, 2 * node + 2);
        }
        const i64 type = 1 - prev_type;
        if (type == 0){
            seg[node] = seg[2 * node + 1] | seg[2 * node + 2];
        } else {
            seg[node] = seg[2 * node + 1] ^ seg[2 * node + 2];
        }
        return type;
    }
};

void solve(){
    i64 n, m;
    cin >> n >> m;

    vector<i64> a(1ll << n);
    for (i64 i = 0; i < (1ll << n); i++){
        cin >> a[i];
    }
    AlternatingORTree seg(a);

    for (i64 i = 0; i < m; i++){
        i64 p, x;
        cin >> p >> x;
        --p;  // to 0-index
        seg.pt_update(p, x, 0, (1ll << n) - 1, 0);
        cout << seg.seg[0] << endl;
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
