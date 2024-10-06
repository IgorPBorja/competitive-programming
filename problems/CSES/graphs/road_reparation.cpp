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

struct DSU {
    vector<i64> p, sizes;
    i64 num_components;

    DSU(i64 n){
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        sizes.assign(n, 1);
        num_components = n;
    }

    i64 find(i64 x){
        while (p[p[x]] != p[x]){ // parent does not point to root
            p[x] = find(p[x]);
        }
        return p[x];
    }

    bool connected(i64 x, i64 y){
        return find(x) == find(y);
    }

    bool unite(i64 x, i64 y){
        i64 rx = find(x), ry = find(y);
        if (rx == ry){
            return false;
        }

        if (sizes[rx] > sizes[ry]){
            swap(rx, ry);
        }
        sizes[ry] += sizes[rx];
        p[rx] = ry;
        --num_components;
        return true;
    }
};

void solve(){
    i64 n, m;
    cin >> n >> m;

    DSU dsu(n);
    vector<tuple<i64, i64, i64>> edges(m);
    for (i64 i = 0; i < m; i++){
        i64 a, b, c;
        cin >> a >> b >> c;
        --a; --b;  // to 0-index
        edges[i] = {c, a, b};
    }

    sort(edges.begin(), edges.end());

    i64 total_cost = 0;
    for (auto[c, a, b]: edges){
        if (dsu.connected(a, b)) {
            continue;
        }
        dsu.unite(a, b);
        total_cost += c;
    }
    // printmsg("parents=", dsu.p.begin(), dsu.p.end());
    // cout << "num components=" << dsu.num_components << endl;
    if (dsu.num_components > 1){
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << total_cost << endl;
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
