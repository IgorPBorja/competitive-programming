//#define TESTCASES
 
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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

struct DSU{
    vector<i64> p;
    vector<i64> size;

    DSU(i64 n){
        p.resize(n);
        size.resize(n);
        for (i64 i = 0; i < n; i++){
            p[i] = i;
            size[i] = 1;
        }
    }

    i64 get(i64 x){
        // update w/ path compression
        if (p[x] != x){
            p[x] = get(p[x]);
            //size[x] = size[p[x]];
        }
        return p[x];
    }

    i64 get_size(i64 x){
        return size[get(x)];
    }

    bool merge(i64 x, i64 y){
        i64 rx = get(x), ry = get(y);
        bool merged = (rx != ry);

        if (size[rx] > size[ry]){
            // small to large: attach smaller piece to larger
            // each component of the merged tree will be visited once if we perform update on all
            // so it makes sense to merge the smaller subtree into the larger
            swap(rx, ry);
        }
        p[rx] = ry; // x -> y

        // we only keep sizes of roots
        // so that we don't need to update size along with the parent in the get method
        size[ry] += size[rx]; // x -> y
        return merged;
    }
};

void solve(){
    i64 n, q;
    cin >> n >> q;

    vector<tuple<i64, i64, i64>> edges(n - 1);
    vector<tuple<i64, i64, i64>> queries(q);
    i64 ans[q];
    for (i64 i = 0; i < n - 1; i++){
        i64 a, b, r;
        cin >> a >> b >> r;

        --a; --b; // fix 1-index
        edges[i] = {-r, a, b};
    }
    for (i64 i = 0; i < q; i++){
        i64 k, v;
        cin >> k >> v;
        --v; // fix 1-index
        queries[i] = {-k, v, i}; // save index for printing later
    }

    sort(edges.begin(), edges.end());
    sort(queries.begin(), queries.end());

    DSU d(n);
    i64 l = -1;

    for (auto[k, v, i]: queries){
        k = -k;
        // merge according to all edges of relevance >= k
        while (l + 1 < n - 1 && -get<0>(edges[l + 1]) >= k){
            d.merge(get<1>(edges[l + 1]), get<2>(edges[l + 1]));
            ++l;
        }
        ans[i] = d.get_size(v) - 1;  // do not count the own node
    }

    for (i64 i = 0; i < q; i++){
        cout << ans[i] << endl;
    }
}
 
signed main(){
	fastio;
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);
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
