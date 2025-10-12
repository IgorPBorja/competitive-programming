// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << " ";} cerr << endl;
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

using tree = vector<vector<i64>>;

// struct HLD {
//     vector<i64> heavy, sz, head, pos, parent;
//     vector<LazySegTree> segs;
//     vector<i64> a, depth;

//     HLD(const tree& adj, const vector<i64>& _a, i64 root = 0) : a(a)
// }

#define int i64
const int MOD = (i64)1e9 + 7;
const int MAX = (i64)1e5 + 10;
const int LOG = 20;

// lazy seg tree
namespace seg {
    int seg[2 * MAX], lazy[2 * MAX];
    int n;

    int junta(int a, int b){
        return (a + b) % MOD;
    }

    // update: multiply everyone by x at node p
    void poe(int p, int x, int tam, bool prop=1){
        seg[p] = (seg[p] * x) % MOD;
        if (prop and p < n) lazy[p] = (lazy[p] * x) % MOD;
    }

    void sobe(int p){
        for (int tam = 2; p /= 2; tam *= 2){
            seg[p] = junta(seg[2 * p], seg[2 * p + 1]);
            poe(p, lazy[p], tam, 0);
        }
    }

    void prop(int p){
        int tam = 1 << (LOG - 1);
        for (int s = LOG; s; s--, tam /= 2){
            int i = p >> s;
            if (lazy[i] != 1){
                poe(2 * i, lazy[i], tam);
                poe(2 * i + 1, lazy[i], tam);
                lazy[i] = 1;  // lazy is multiplicative!!!
            }
        }
    }

    void build(int n2, int* v){
        n = n2;
        for (int i = 0; i < n; i++) seg[n + i] = v[i];
        for (int i = n - 1; i; i--) seg[i] = junta(seg[2 * i], seg[2 * i + 1]);
        for (int i = 0; i < 2 * n; i++) lazy[i] = 1;  // lazy is multiplicative!!!
        // printmsg("seg=", seg, seg + 2 * n);
    }

    int query(int a, int b){
        // ++a; ++b;  // 1-index
        // cerr << "seg query at a=" << a << " b=" << b << endl;
        int ret = 0;
        for (prop(a += n), prop(b += n); a <= b; ++a/=2, --b/=2){
            // cerr << "nodes at a=" << a << " b=" << b << " ret=" << ret << endl;
            if (a % 2 == 1) ret = junta(ret, seg[a]);
            if (b % 2 == 0) ret = junta(ret, seg[b]);
        }
        return ret;
    }

    void update(int a, int b, int x){
        // ++a; ++b;  // 1-index
        // cerr << "seg update at a=" << a << " b=" << b << endl;
        int a2 = a += n, b2 = b += n, tam = 1;
        for (; a <= b; ++a/=2, --b/=2, tam *= 2){
            if (a % 2 == 1) poe(a, x, tam);
            if (b % 2 == 0) poe(b, x, tam);
        }
        sobe(a2), sobe(b2);
    }
}

namespace hld {
    vector<pair<int, int>> g[MAX];
    int pos[MAX], sz[MAX];
    int sobe[MAX], pai[MAX];
    int h[MAX], v[MAX], t;

    void build_hld(int k, int p = -1, int f = 1){
        v[pos[k] = t++] = sobe[k]; sz[k] = 1;
        for (auto& i: g[k]) if (i.first != p){
            auto[u, w] = i;
            sobe[u] = w; pai[u] = k;
            h[u] = (i == g[k][0] ? h[k] : u);
            build_hld(u, k, f); sz[k] += sz[u];

            if (sz[u] > sz[g[k][0].first] or g[k][0].first == p)
                swap(i, g[k][0]);
        }
        if (p * f == -1) build_hld(h[k] = k, -1, t = 0);
    }
    void build(int root = 0){
        t = 1;  // 1-index positions
        build_hld(root);
        // cerr << "t=" << t << endl;
        seg::build(t, v);
    }
    int query_path(int a, int b){
        // cerr << "hld query at a=" << a << " b=" << b << endl;
        if (a == b) return 0;
        if (pos[a] < pos[b]) swap(a, b);
        if (h[a] == h[b]) return seg::query(pos[b]+1, pos[a]);
        return (seg::query(pos[h[a]], pos[a]) + query_path(pai[h[a]], b)) % MOD;
    }
    void update_path(int a, int b, int x){
        // cerr << "hld update at a=" << a << " b=" << b << " x=" << x << endl;
        if (a == b) return;
        if (pos[a] < pos[b]) swap(a, b);
        if (h[a] == h[b]) return (void)seg::update(pos[b]+1, pos[a], x);
        seg::update(pos[h[a]], pos[a], x); update_path(pai[h[a]], b, x);
    }
}

void solve(){
    i64 n, q;
    cin >> n >> q;
    for (i64 i = 0; i < n - 1; i++){
        i64 u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        hld::g[u].emplace_back(v, w);
        hld::g[v].emplace_back(u, w);
    }

    hld::build();
    // cerr << "build ok" << endl;

    for (i64 i = 0; i < q; i++){
        i64 u, v, x;
        cin >> u >> v >> x;
        --u; --v;
        hld::update_path(u, v, x);
        // printmsg("seg=", seg::seg, seg::seg + 2 * n);
        // cerr << "update ok" << endl;
        // printmsg("seg=", seg::seg, seg::seg + 2 * n);
        cout << hld::query_path(u, v) << endl;
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
