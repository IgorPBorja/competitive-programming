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

struct Node {
    i64 minp, sum;

    Node() : minp(0), sum(0) {}
    Node(i64 minp, i64 sum) : minp(minp), sum(sum) {}
    friend ostream& operator<<(ostream& os, Node n){
        // os << "(minp=" << n.minp << ",sum=" << n.sum << ")";
        os << "(" << n.minp << "," << n.sum << ")";
        return os;
    }
};

// min prefix sum over range
// range represents cyclic array
struct MinPrefixSeg {
    vector<Node> seg;
    vector<i64> b, c;
    i64 n, tn;

    Node merge(Node n1, Node n2){
        return Node(
            min(n1.minp, n1.sum + n2.minp),
            n1.sum + n2.sum
        );
    }

    // tn = tree size (num nodes)
    MinPrefixSeg(const vector<i64> _b, const vector<i64> _c) : n(_b.size()), tn(2 * n) {
        seg.resize(4 * tn);
        b.resize(tn);
        c.resize(tn);

        copy(all(_b), b.begin());
        copy(all(_b), b.begin() + n);
        copy(all(_c), c.begin());
        copy(all(_c), c.begin() + n);

        // build
        for (i64 i = 0; i < n; i++){
            update_b(i, _b[i]);
            update_c(i, _c[i]);
        }
        // printmsg("seg=", seg.begin(), seg.end());
        // debug << "build ok" << endl;
        // debug << "tn=" << tn << " n=" << n << endl;
    }

    void _update(i64 p, i64 x, i64 y, i64 tl, i64 tr, i64 node){
        if (tl == p && p == tr){
            b[p] = x;
            c[p] = y;
            seg[node] = Node(b[p] - c[p], b[p] - c[p]);
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (p <= tm) _update(p, x, y, tl, tm, 2 * node + 1);
            else _update(p, x, y, tm + 1, tr, 2 * node + 2);
            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    void update_b(i64 p, i64 x){
        _update(p, x, c[p], 0, tn - 1, 0);
        _update(p + n, x, c[p + n], 0, tn - 1, 0);
    }

    void update_c(i64 p, i64 x){
        _update(p, b[p], x, 0, tn - 1, 0);
        _update(p + n, b[p + n], x, 0, tn - 1, 0);
    }

    Node _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        const i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr) return seg[node];
        else {
            if (r <= tm) return _query(l, r, tl, tm, 2 * node + 1);
            else if (l > tm) return _query(l, r, tm + 1, tr, 2 * node + 2);
            else return merge(
                _query(l, tm, tl, tm, 2 * node + 1),
                _query(tm + 1, r, tm + 1, tr, 2 * node + 2)
            );
        }
    }

    Node query(i64 l, i64 r){
        return _query(l, r, 0, tn - 1, 0);
    }

    /*
    find first negative prefixsum from start index i

    If largest non-negative prefix is from i to ans then answer is ans+1
    */
    i64 bsearch(const i64 i){
        i64 ans = i - 1;
        i64 l = i, r = i + n - 1;  // if [i, i+n-1] is non-negative then we have full cycle
        while (l <= r){
            const i64 m = l + (r - l) / 2;
            // debug << "l=" << l << " m=" << m << " r=" << r << endl;
            i64 minp = query(i, m).minp;
            // debug << "query(i=" << i << ",m=" << m << ")=" << minp << endl;
            if (minp >= 0){
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        if (ans + 1 == i + n){
            return -1;
        }
        // already return 1-indexed
        i64 first_negative = (ans + 1) % n;
        return first_negative + 1;
    }
};

void solve(){
    i64 n, q;
    cin >> n >> q;

    vector<i64> b(n), c(n);
    for (i64 i = 0; i < n; i++) cin >> b[i];
    for (i64 i = 0; i < n; i++) cin >> c[i];

    MinPrefixSeg seg(b, c);

    for (i64 _ = 0; _ < q; _++){
        i64 mode, i, x;
        cin >> mode >> i;
        --i;  // 0-index
        if (mode == 1){
            cout << seg.bsearch(i) << endl;
        } else if (mode == 2){
            cin >> x;
            seg.update_b(i, x);
        } else {
            cin >> x;
            seg.update_c(i, x);
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
